import streamlit as st
import json
import random

class RoguelikeGame:
    def __init__(self):
        self.load_data()
    
    def load_data(self):
        try:
            with open('game_data.json', 'r') as f:
                self.data = json.load(f)
        except FileNotFoundError:
            self.reset_game()
    
    def save_data(self):
        with open('game_data.json', 'w') as f:
            json.dump(self.data, f, indent=2)
    
    def reset_game(self):
        self.data = {
            "player": {"health": 10.0, "max_health": 10.0, "attack": 1, "defense": 0.0, "room": 1, "coins": 0},
            "enemies": [
                {"name": "Goblin", "health": 5, "attack": 1, "coin_min": 1, "coin_max": 5},
                {"name": "Orc", "health": 8, "attack": 2, "coin_min": 7, "coin_max": 10},
                {"name": "Skeleton", "health": 6, "attack": 1, "coin_min": 2, "coin_max": 6},
                {"name": "Wolf", "health": 4, "attack": 2, "coin_min": 3, "coin_max": 6}
            ],
            "bosses": [
                {"name": "Troll King", "health": 25, "attack": 4, "coin_min": 10, "coin_max": 13},
                {"name": "Dragon", "health": 40, "attack": 6, "coin_min": 17, "coin_max": 20},
                {"name": "Lich", "health": 35, "attack": 5, "coin_min": 14, "coin_max": 16}
            ],
            "perks": [
                {"name": "Health Boost", "type": "health", "value": 5},
                {"name": "Attack Up", "type": "attack", "value": 1},
                {"name": "Defense Up", "type": "defense", "value": 0.1},
                {"name": "Max Health Up", "type": "max_health", "value": 3},
                {"name": "Strong Attack", "type": "attack", "value": 2},
                {"name": "Shield", "type": "defense", "value": 0.15}
            ]
        }

    def apply_perk(self, perk):
        p = self.data["player"]
        if perk['type'] == 'health':
            p['health'] = min(p['max_health'], p['health'] + perk['value'])
        elif perk['type'] == 'max_health':
            p['max_health'] += perk['value']
            p['health'] += perk['value']
        elif perk['type'] == 'attack':
            p['attack'] += perk['value']
        elif perk['type'] == 'defense':
            p['defense'] = min(1.0, p['defense'] + perk['value'])

# Initialize session state
def init_session_state():
    defaults = {
        'game': RoguelikeGame(),
        'game_started': False,
        'current_enemy': None,
        'current_boss': None,
        'available_perks': None,
        'combat_messages': [],
        'boss_messages': [],
        'intelligence_messages': [],
        'intelligence_result': None,
        'math_problem': None,
        'shop_active': False,
        'shop_perks': None,
        'purchased_perks': [],
        'room_state': 'menu'  # menu, room_select, combat, intelligence, boss, perk, shop
    }
    
    for key, value in defaults.items():
        if key not in st.session_state:
            st.session_state[key] = value

def get_room_type():
    """Determine what type of room the player should be in"""
    p = st.session_state.game.data["player"]
    room = p['room']
    
    if room == 4:
        return 'shop'
    elif room % 10 == 0:
        return 'boss'
    else:
        return 'regular'

def show_stats():
    p = st.session_state.game.data["player"]
    col1, col2, col3, col4, col5 = st.columns([1, 2, 1, 1, 1])
    with col1:
        st.metric("📍 Room", p['room'])
    with col2:
        st.metric("❤️ Health", f"{p['health']:.2f}/{p['max_health']:.2f}")
    with col3:
        st.metric("🗡️ Attack", p['attack'])
    with col4:
        st.metric("🛡️ Defense", f"{p['defense']:.2f}")
    with col5:
        st.metric("🪙 Coins", p['coins'])

def show_menu():
    st.subheader("Welcome to the Roguelike Game!")
    col1, col2 = st.columns(2)
    with col1:
        if st.button("🆕 New Game", use_container_width=True):
            st.session_state.game.reset_game()
            st.session_state.game.save_data()
            st.session_state.game_started = True
            st.session_state.room_state = get_room_type()
            st.rerun()
    with col2:
        if st.button("▶️ Continue Game", use_container_width=True):
            st.session_state.game_started = True
            st.session_state.room_state = get_room_type()
            st.rerun()

def show_room_select():
    st.subheader("Choose Room Type")
    col1, col2 = st.columns(2)
    with col1:
        if st.button("⚔️ Combat Room", use_container_width=True):
            st.session_state.room_state = 'combat'
            st.rerun()
    with col2:
        if st.button("🧠 Intelligence Room", use_container_width=True):
            st.session_state.room_state = 'intelligence'
            st.rerun()

def show_combat():
    if st.session_state.current_enemy is None:
        st.session_state.current_enemy = random.choice(st.session_state.game.data["enemies"]).copy()
    
    enemy = st.session_state.current_enemy
    p = st.session_state.game.data["player"]
    
    st.subheader("⚔️ Combat Room")
    st.write(f"**{enemy['name']}** - Health: {enemy['health']}, Attack: {enemy['attack']}")
    
    for msg in st.session_state.combat_messages:
        st.write(msg)
    
    if st.button("🗡️ Attack"):
        st.session_state.combat_messages = []
        enemy['health'] -= p['attack']
        st.session_state.combat_messages.append(f"You deal {p['attack']} damage!")
        
        if enemy['health'] <= 0:
            coins_dropped = random.randint(enemy['coin_min'], enemy['coin_max'])
            p['coins'] += coins_dropped
            st.session_state.combat_messages.append(f"{enemy['name']} defeated! You found {coins_dropped} coins!")
            st.session_state.current_enemy = None
            st.session_state.combat_messages = []
            st.session_state.available_perks = random.sample(st.session_state.game.data["perks"], 3)
            st.session_state.room_state = 'perk'
        else:
            damage = enemy['attack'] * (1 - p['defense'])
            actual_damage = max(1.0, damage)
            p['health'] -= actual_damage
            st.session_state.combat_messages.append(f"{enemy['name']} deals {actual_damage:.2f} damage!")
            st.session_state.combat_messages.append(f"Health: {p['health']:.2f}/{p['max_health']:.2f}")
        
        st.session_state.game.save_data()
        st.rerun()

def show_intelligence():
    if st.session_state.intelligence_result is not None:
        result = st.session_state.intelligence_result
        st.subheader("🧠 Intelligence Room")
        
        if result['correct']:
            st.success("Correct! You gain wisdom.")
        else:
            st.error(f"Wrong! Your answer: {result['user_answer']}, Correct answer: {result['correct_answer']}")
            st.write(f"You take {result['damage']} damage!")
        
        if st.button("Continue", use_container_width=True):
            st.session_state.intelligence_result = None
            st.session_state.math_problem = None
            if result['correct']:
                st.session_state.available_perks = random.sample(st.session_state.game.data["perks"], 3)
                st.session_state.room_state = 'perk'
            else:
                p = st.session_state.game.data["player"]
                p['room'] += 1
                st.session_state.room_state = get_room_type()
            st.session_state.game.save_data()
            st.rerun()
    else:
        if st.session_state.math_problem is None:
            a = random.randint(1, 20)
            b = random.randint(1, 20)
            operation = random.choice(['+', '-', '*'])
            answer = a + b if operation == '+' else a - b if operation == '-' else a * b
            st.session_state.math_problem = {"a": a, "b": b, "op": operation, "answer": answer}
        
        problem = st.session_state.math_problem
        st.subheader("🧠 Intelligence Room")
        st.write(f"Solve: {problem['a']} {problem['op']} {problem['b']} = ?")
        
        user_answer = st.number_input("Your answer:", step=1, format="%d")
        
        if st.button("Submit Answer"):
            p = st.session_state.game.data["player"]
            if user_answer == problem['answer']:
                st.session_state.intelligence_result = {'correct': True, 'user_answer': user_answer, 'correct_answer': problem['answer']}
            else:
                damage = random.randint(1, 3)
                p['health'] -= damage
                st.session_state.intelligence_result = {'correct': False, 'user_answer': user_answer, 'correct_answer': problem['answer'], 'damage': damage}
            st.session_state.game.save_data()
            st.rerun()

def show_boss():
    p = st.session_state.game.data["player"]
    
    if st.session_state.current_boss is None:
        st.subheader("👹 Boss Room")
        if st.button("⚔️ Enter Boss Room", use_container_width=True):
            boss_index = (p['room'] // 10) - 1
            if boss_index >= len(st.session_state.game.data["bosses"]):
                boss_index = len(st.session_state.game.data["bosses"]) - 1
            st.session_state.current_boss = st.session_state.game.data["bosses"][boss_index].copy()
            st.rerun()
    else:
        boss = st.session_state.current_boss
        st.subheader("👹 Boss Fight")
        st.write(f"**{boss['name']}** - Health: {boss['health']}, Attack: {boss['attack']}")
        
        for msg in st.session_state.boss_messages:
            st.write(msg)
        
        if st.button("⚔️ Attack Boss"):
            st.session_state.boss_messages = []
            boss['health'] -= p['attack']
            st.session_state.boss_messages.append(f"You deal {p['attack']} damage!")
            
            if boss['health'] <= 0:
                coins_dropped = random.randint(boss['coin_min'], boss['coin_max'])
                p['coins'] += coins_dropped
                st.session_state.boss_messages.append(f"{boss['name']} defeated! You found {coins_dropped} coins!")
                st.session_state.current_boss = None
                st.session_state.boss_messages = []
                st.session_state.available_perks = random.sample(st.session_state.game.data["perks"], 3)
                st.session_state.room_state = 'perk'
                st.session_state.shop_active = True  # Trigger shop after boss
            else:
                damage = boss['attack'] * (1 - p['defense'])
                actual_damage = max(1.0, damage)
                p['health'] -= actual_damage
                st.session_state.boss_messages.append(f"{boss['name']} deals {actual_damage:.2f} damage!")
                st.session_state.boss_messages.append(f"Health: {p['health']:.2f}/{p['max_health']:.2f}")
            
            st.session_state.game.save_data()
            st.rerun()

def show_perk():
    st.subheader("🎁 Choose a Perk")
    st.info("You must choose a perk before proceeding to the next room.")
    
    for i, perk in enumerate(st.session_state.available_perks):
        if st.button(f"{perk['name']} (+{perk['value']} {perk['type']})", key=f"perk_{i}"):
            st.session_state.game.apply_perk(perk)
            st.success(f"You gained {perk['name']}!")
            st.session_state.available_perks = None
            
            p = st.session_state.game.data["player"]
            if st.session_state.shop_active:
                st.session_state.room_state = 'shop'
                st.session_state.shop_perks = random.sample(st.session_state.game.data["perks"], 3)
                st.session_state.purchased_perks = []
            else:
                p['room'] += 1
                st.session_state.room_state = get_room_type()
            
            st.session_state.game.save_data()
            st.rerun()

def show_shop():
    p = st.session_state.game.data["player"]
    
    if st.session_state.shop_perks is None:
        st.session_state.shop_perks = random.sample(st.session_state.game.data["perks"], 3)
        st.session_state.purchased_perks = []
    
    st.subheader("🏪 Shop")
    st.write(f"Welcome to the shop! Each perk costs 8 coins.")
    st.write(f"Your coins: {p['coins']}")
    
    for i, perk in enumerate(st.session_state.shop_perks):
        status = "SOLD" if i in st.session_state.purchased_perks else "Available"
        disabled = i in st.session_state.purchased_perks or p['coins'] < 8
        
        if st.button(f"{perk['name']} (+{perk['value']} {perk['type']}) - 8 coins ({status})", 
                    key=f"shop_perk_{i}", disabled=disabled):
            if i not in st.session_state.purchased_perks and p['coins'] >= 8:
                p['coins'] -= 8
                st.session_state.game.apply_perk(perk)
                st.session_state.purchased_perks.append(i)
                st.success(f"You bought {perk['name']}!")
                st.session_state.game.save_data()
                st.rerun()
    
    if st.button("Leave Shop", use_container_width=True):
        st.session_state.shop_perks = None
        st.session_state.purchased_perks = []
        st.session_state.shop_active = False
        p['room'] += 1
        st.session_state.room_state = get_room_type()
        st.session_state.game.save_data()
        st.rerun()

# Main app
init_session_state()
st.title("🗡️ Roguelike Game")

# Game over check
p = st.session_state.game.data["player"]
if st.session_state.game_started and p['health'] <= 0:
    st.error("💀 GAME OVER!")
    if st.button("Start New Game"):
        st.session_state.game.reset_game()
        st.session_state.game.save_data()
        st.session_state.room_state = 'menu'
        st.session_state.game_started = False
        st.rerun()
    st.stop()

# Show stats if game started
if st.session_state.game_started:
    show_stats()
    st.divider()

# Route to appropriate screen
if not st.session_state.game_started or st.session_state.room_state == 'menu':
    show_menu()
elif st.session_state.room_state == 'room_select':
    show_room_select()
elif st.session_state.room_state == 'combat':
    show_combat()
elif st.session_state.room_state == 'intelligence':
    show_intelligence()
elif st.session_state.room_state == 'boss':
    show_boss()
elif st.session_state.room_state == 'perk':
    show_perk()
elif st.session_state.room_state == 'shop':
    show_shop()
elif st.session_state.room_state == 'regular':
    show_room_select()