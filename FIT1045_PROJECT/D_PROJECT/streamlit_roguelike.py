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

# Initialize game
if 'game' not in st.session_state:
    st.session_state.game = RoguelikeGame()
if 'current_enemy' not in st.session_state:
    st.session_state.current_enemy = None
if 'current_boss' not in st.session_state:
    st.session_state.current_boss = None
if 'math_problem' not in st.session_state:
    st.session_state.math_problem = None
if 'available_perks' not in st.session_state:
    st.session_state.available_perks = None
if 'room_chosen' not in st.session_state:
    st.session_state.room_chosen = None
if 'game_started' not in st.session_state:
    st.session_state.game_started = False
if 'combat_messages' not in st.session_state:
    st.session_state.combat_messages = []
if 'boss_messages' not in st.session_state:
    st.session_state.boss_messages = []
if 'intelligence_messages' not in st.session_state:
    st.session_state.intelligence_messages = []
if 'intelligence_result' not in st.session_state:
    st.session_state.intelligence_result = None
if 'shop_perks' not in st.session_state:
    st.session_state.shop_perks = None
if 'purchased_perks' not in st.session_state:
    st.session_state.purchased_perks = []
if 'boss_just_defeated' not in st.session_state:
    st.session_state.boss_just_defeated = False

st.title("🗡️ Roguelike Game")

# Initial game selection
if not st.session_state.game_started:
    st.subheader("Welcome to the Roguelike Game!")
    
    col1, col2 = st.columns(2)
    with col1:
        if st.button("🆕 New Game", use_container_width=True):
            st.session_state.game.reset_game()
            st.session_state.game.save_data()
            st.session_state.game_started = True
            st.rerun()
    
    with col2:
        if st.button("▶️ Continue Game", use_container_width=True):
            st.session_state.game_started = True
            st.rerun()
    
    st.stop()

# Display player stats
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

st.divider()

# Game over check
if p['health'] <= 0:
    st.error("💀 GAME OVER!")
    if st.button("Start New Game"):
        st.session_state.game.reset_game()
        st.session_state.game.save_data()
        st.rerun()

# Main game logic
elif st.session_state.shop_perks is not None and p['room'] != 4:  # Shop room (after boss defeat)
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
        st.session_state.game.save_data()
        st.rerun()

elif p['room'] == 4:  # First shop room
    st.session_state.room_chosen = None  # Clear room selection for special room
    if st.session_state.shop_perks is None:
        st.session_state.shop_perks = random.sample(st.session_state.game.data["perks"], 3)
        st.session_state.purchased_perks = []
        st.session_state.boss_just_defeated = False  # Ensure this is not a post-boss shop
    
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
        p['room'] += 1
        st.session_state.game.save_data()
        st.rerun()

elif p['room'] % 10 == 0:  # Boss room
    st.session_state.room_chosen = None  # Clear room selection for special room
    st.subheader("👹 Boss Room")
    
    if st.button("⚔️ Enter Boss Room", use_container_width=True):
        boss_index = (p['room'] // 10) - 1
        if boss_index >= len(st.session_state.game.data["bosses"]):
            boss_index = len(st.session_state.game.data["bosses"]) - 1
        st.session_state.current_boss = st.session_state.game.data["bosses"][boss_index].copy()
        p['room'] += 1
        st.session_state.game.save_data()
        st.rerun()

elif st.session_state.current_boss is not None:  # In boss fight
    boss = st.session_state.current_boss
    st.subheader("👹 Boss Fight")
    st.write(f"**{boss['name']}** - Health: {boss['health']}, Attack: {boss['attack']}")
    
    # Display boss messages
    for msg in st.session_state.boss_messages:
        st.write(msg)
    
    if st.button("⚔️ Attack Boss"):
        st.session_state.boss_messages = []  # Clear previous messages
        boss['health'] -= p['attack']
        st.session_state.boss_messages.append(f"You deal {p['attack']} damage!")
        
        if boss['health'] <= 0:
            coins_dropped = random.randint(boss['coin_min'], boss['coin_max'])
            p['coins'] += coins_dropped
            st.session_state.boss_messages.append(f"{boss['name']} defeated! You found {coins_dropped} coins!")
            st.session_state.current_boss = None
            st.session_state.boss_messages = []
            st.session_state.boss_just_defeated = True
            st.session_state.available_perks = random.sample(st.session_state.game.data["perks"], 3)
        else:
            damage = boss['attack'] * (1 - p['defense'])
            actual_damage = max(1.0, damage)
            p['health'] -= actual_damage
            st.session_state.boss_messages.append(f"{boss['name']} deals {actual_damage:.2f} damage ({boss['attack']} * {1 - p['defense']:.2f} = {damage:.2f})!")
            st.session_state.boss_messages.append(f"Health: {p['health']:.2f}/{p['max_health']:.2f}")
            st.session_state.current_boss = boss
        
        st.session_state.game.save_data()
        st.rerun()

# Perk selection (must be completed before room selection)
elif st.session_state.available_perks is not None:
    st.subheader("🎁 Choose a Perk")
    
    # Display intelligence messages if any
    for msg in st.session_state.intelligence_messages:
        if "Wrong!" in msg:
            st.error(msg)
        elif "damage" in msg:
            st.write(msg)
        else:
            st.success(msg)
    
    st.info("You must choose a perk before proceeding to the next room.")
    for i, perk in enumerate(st.session_state.available_perks):
        if st.button(f"{perk['name']} (+{perk['value']} {perk['type']})", key=f"perk_{i}"):
            st.session_state.game.apply_perk(perk)
            st.success(f"You gained {perk['name']}!")
            st.session_state.available_perks = None
            st.session_state.intelligence_messages = []  # Clear intelligence messages
            
            # Check if shop should appear after boss defeat
            if st.session_state.boss_just_defeated:
                st.session_state.shop_perks = random.sample(st.session_state.game.data["perks"], 3)
                st.session_state.purchased_perks = []
                st.session_state.boss_just_defeated = False
            
            st.session_state.game.save_data()
            st.rerun()

else:  # Regular room
    if st.session_state.room_chosen is None:
        st.subheader("Choose Room Type")
        col1, col2 = st.columns(2)
        
        with col1:
            if st.button("⚔️ Combat Room", use_container_width=True):
                st.session_state.room_chosen = "Combat"
                p['room'] += 1
                st.session_state.game.save_data()
                st.rerun()
        
        with col2:
            if st.button("🧠 Intelligence Room", use_container_width=True):
                st.session_state.room_chosen = "Intelligence"
                p['room'] += 1
                st.session_state.game.save_data()
                st.rerun()
    
    else:
        room_type = st.session_state.room_chosen
        
        if room_type == "Combat":
            if st.session_state.current_enemy is None:
                st.session_state.current_enemy = random.choice(st.session_state.game.data["enemies"]).copy()
            
            enemy = st.session_state.current_enemy
            st.subheader("⚔️ Combat Room")
            st.write(f"**{enemy['name']}** - Health: {enemy['health']}, Attack: {enemy['attack']}")
            
            # Display combat messages
            for msg in st.session_state.combat_messages:
                st.write(msg)
            
            if st.button("🗡️ Attack"):
                st.session_state.combat_messages = []  # Clear previous messages
                enemy['health'] -= p['attack']
                st.session_state.combat_messages.append(f"You deal {p['attack']} damage!")
                
                if enemy['health'] <= 0:
                    coins_dropped = random.randint(enemy['coin_min'], enemy['coin_max'])
                    p['coins'] += coins_dropped
                    st.session_state.combat_messages.append(f"{enemy['name']} defeated! You found {coins_dropped} coins!")
                    st.session_state.current_enemy = None
                    st.session_state.room_chosen = None
                    st.session_state.combat_messages = []
                    st.session_state.available_perks = random.sample(st.session_state.game.data["perks"], 3)
                else:
                    damage = enemy['attack'] * (1 - p['defense'])
                    actual_damage = max(1.0, damage)
                    p['health'] -= actual_damage
                    st.session_state.combat_messages.append(f"{enemy['name']} deals {actual_damage:.2f} damage ({enemy['attack']} * {1 - p['defense']:.2f} = {damage:.2f})!")
                    st.session_state.combat_messages.append(f"Health: {p['health']:.2f}/{p['max_health']:.2f}")
                    st.session_state.current_enemy = enemy
                
                st.session_state.game.save_data()
                st.rerun()
        
        else:  # Intelligence room
            if st.session_state.intelligence_result is not None:
                # Show result and wait for user to continue
                st.subheader("🧠 Intelligence Room")
                result = st.session_state.intelligence_result
                
                if result['correct']:
                    st.success("Correct! You gain wisdom.")
                else:
                    st.error(f"Wrong! Your answer: {result['user_answer']}, Correct answer: {result['correct_answer']}")
                    st.write(f"You take {result['damage']} damage due to mental confusion from the wrong answer!")
                
                if st.button("Continue", use_container_width=True):
                    st.session_state.intelligence_result = None
                    st.session_state.math_problem = None
                    st.session_state.room_chosen = None
                    if result['correct']:
                        st.session_state.available_perks = random.sample(st.session_state.game.data["perks"], 3)
                    st.session_state.game.save_data()
                    st.rerun()
            
            else:
                # Show math problem
                if st.session_state.math_problem is None:
                    a = random.randint(1, 20)
                    b = random.randint(1, 20)
                    operation = random.choice(['+', '-', '*'])
                    if operation == '+':
                        answer = a + b
                    elif operation == '-':
                        answer = a - b
                    else:
                        answer = a * b
                    st.session_state.math_problem = {"a": a, "b": b, "op": operation, "answer": answer}
                
                problem = st.session_state.math_problem
                st.subheader("🧠 Intelligence Room")
                st.write(f"Solve: {problem['a']} {problem['op']} {problem['b']} = ?")
                
                user_answer = st.number_input("Your answer:", step=1, format="%d")
                
                if st.button("Submit Answer"):
                    if user_answer == problem['answer']:
                        st.session_state.intelligence_result = {'correct': True, 'user_answer': user_answer, 'correct_answer': problem['answer']}
                    else:
                        damage = random.randint(1, 3)
                        p['health'] -= damage
                        st.session_state.intelligence_result = {'correct': False, 'user_answer': user_answer, 'correct_answer': problem['answer'], 'damage': damage}
                    
                    st.session_state.game.save_data()
                    st.rerun()

