import streamlit as st
import json
import random
import math

class RoguelikeGame:
    def __init__(self):
        self.load_data()
    
    def load_data(self):
        try:
            with open('advanced_game_data.json', 'r') as f:
                self.data = json.load(f)
        except FileNotFoundError:
            self.reset_game()
    
    def save_data(self):
        with open('advanced_game_data.json', 'w') as f:
            json.dump(self.data, f, indent=2)
    
    def reset_game(self):
        self.data = {
            "player": {
                "health": 10.0, "max_health": 10.0, "attack": 1, "defense": 0.0, 
                "agility": 0.0, "mana": 0, "coins": 0, "room": 1, "class": None
            },
            "allies": [],
            "unique_perks_obtained": [],
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
            "superbosses": [
                {"name": "Ancient Titan", "health": 100, "attack": 12, "coin_min": 50, "coin_max": 75},
                {"name": "Void Lord", "health": 150, "attack": 15, "coin_min": 75, "coin_max": 100}
            ],
            "allies_pool": [
                {"name": "Knight", "health": 15, "attack": 2, "defense": 0.1},
                {"name": "Archer", "health": 10, "attack": 3, "agility": 0.2},
                {"name": "Healer", "health": 8, "attack": 1, "healing": 2},
                {"name": "Warrior", "health": 20, "attack": 2, "defense": 0.05}
            ],
            "common_perks": [
                {"name": "Health Boost", "type": "health", "value": 5, "rarity": "common"},
                {"name": "Attack Up", "type": "attack", "value": 1, "rarity": "common"},
                {"name": "Defense Up", "type": "defense", "value": 0.1, "rarity": "common"},
                {"name": "Agility Up", "type": "agility", "value": 0.05, "rarity": "common"}
            ],
            "rare_perks": [
                {"name": "Strong Attack", "type": "attack", "value": 2, "rarity": "rare"},
                {"name": "Shield Master", "type": "defense", "value": 0.15, "rarity": "rare"},
                {"name": "Swift Dodge", "type": "agility", "value": 0.1, "rarity": "rare"},
                {"name": "Mana Boost", "type": "mana", "value": 3, "rarity": "rare"}
            ],
            "unique_perks": [
                {"name": "Titan's Strength", "type": "attack", "value": 5, "rarity": "unique"},
                {"name": "Void Shield", "type": "defense", "value": 0.3, "rarity": "unique"},
                {"name": "Time Warp", "type": "agility", "value": 0.25, "rarity": "unique"}
            ],
            "riddles": [
                {"question": "What has keys but no locks, space but no room, you can enter but not go inside?", "answer": "keyboard"},
                {"question": "I am not alive, but I grow; I don't have lungs, but I need air; I don't have a mouth, but water kills me. What am I?", "answer": "fire"},
                {"question": "What comes once in a minute, twice in a moment, but never in a thousand years?", "answer": "m"},
                {"question": "What has hands but cannot clap?", "answer": "clock"},
                {"question": "What gets wet while drying?", "answer": "towel"}
            ]
        }

    def get_class_stats(self, class_name):
        classes = {
            "swordmaster": {"health": 12, "attack": 2, "defense": 0.05, "agility": 0.1, "mana": 0},
            "archer": {"health": 8, "attack": 1, "defense": 0.0, "agility": 0.2, "mana": 0},
            "tank": {"health": 15, "attack": 1, "defense": 0.15, "agility": 0.0, "mana": 0},
            "mage": {"health": 6, "attack": 1, "defense": 0.0, "agility": 0.05, "mana": 5}
        }
        return classes.get(class_name, classes["swordmaster"])

    def apply_mage_buffs(self):
        p = self.data["player"]
        if p["class"] == "mage" and p["mana"] > 0:
            # Attack buff for party
            attack_boost = math.floor(p["mana"] * 0.5)
            # Healing for party
            healing = p["mana"] * 0.1
            
            # Heal player
            p["health"] = min(p["max_health"], p["health"] + healing)
            
            # Heal allies
            for ally in self.data["allies"]:
                ally["health"] = min(ally["max_health"], ally["health"] + healing)
            
            return attack_boost, healing
        return 0, 0

    def get_total_party_attack(self):
        p = self.data["player"]
        total_attack = p["attack"]
        
        # Add mage buff
        if p["class"] == "mage":
            total_attack += math.floor(p["mana"] * 0.5)
        
        # Add ally attacks
        for ally in self.data["allies"]:
            total_attack += ally["attack"]
        
        return total_attack

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
        elif perk['type'] == 'agility':
            p['agility'] = min(1.0, p['agility'] + perk['value'])
        elif perk['type'] == 'mana':
            p['mana'] += perk['value']

    def get_available_perks(self, room, is_boss=False, is_superboss=False):
        if is_superboss:
            # Unique perks from superboss
            available_unique = [p for p in self.data["unique_perks"] if p["name"] not in self.data["unique_perks_obtained"]]
            return available_unique[:1] if available_unique else []
        
        perks = []
        if room <= 30:
            perks = self.data["common_perks"]
        else:
            perks = self.data["common_perks"] + self.data["rare_perks"]
        
        if is_boss and room > 30:
            perks = self.data["rare_perks"]
        
        return random.sample(perks, min(3, len(perks)))

def init_session_state():
    defaults = {
        'game': RoguelikeGame(),
        'game_started': False,
        'class_selected': False,
        'current_enemy': None,
        'current_boss': None,
        'current_superboss': None,
        'available_perks': None,
        'combat_messages': [],
        'boss_messages': [],
        'ally_messages': [],
        'riddle_result': None,
        'current_riddle': None,
        'intelligence_result': None,
        'math_problem': None,
        'shop_active': False,
        'shop_perks': None,
        'purchased_perks': [],
        'room_state': 'menu'
    }
    
    for key, value in defaults.items():
        if key not in st.session_state:
            st.session_state[key] = value

def get_room_type():
    p = st.session_state.game.data["player"]
    room = p['room']
    
    if room == 4:
        return 'shop'
    elif room % 50 == 0:
        return 'superboss'
    elif room % 10 == 0:
        return 'boss'
    else:
        # Random ally encounter (low chance, increases with room)
        ally_chance = min(0.05 + (room / 1000), 0.15) if room < 40 else min(0.1 + (room / 500), 0.25)
        if random.random() < ally_chance and len(st.session_state.game.data["allies"]) < 3:
            return 'ally'
        return 'regular'

def show_stats():
    p = st.session_state.game.data["player"]
    allies = st.session_state.game.data["allies"]
    
    # Player stats
    col1, col2, col3, col4, col5, col6, col7 = st.columns([1, 2, 1, 1, 1, 1, 1])
    with col1:
        st.metric("📍 Room", p['room'])
    with col2:
        st.metric("❤️ Health", f"{p['health']:.1f}/{p['max_health']:.1f}")
    with col3:
        st.metric("🗡️ Attack", p['attack'])
    with col4:
        st.metric("🛡️ Defense", f"{p['defense']:.2f}")
    with col5:
        st.metric("⚡ Agility", f"{p['agility']:.2f}")
    with col6:
        st.metric("🔮 Mana", p['mana'] if p['class'] == 'mage' else 'N/A')
    with col7:
        st.metric("🪙 Coins", p['coins'])
    
    # Show class and allies
    st.write(f"**Class:** {p['class'].title() if p['class'] else 'None'}")
    if allies:
        st.write("**Allies:**")
        for ally in allies:
            st.write(f"- {ally['name']}: {ally['health']:.1f}/{ally['max_health']:.1f} HP, {ally['attack']} ATK")

def show_class_selection():
    st.subheader("Choose Your Class")
    
    classes = {
        "swordmaster": "⚔️ Swordmaster - Balanced fighter with good attack and defense",
        "archer": "🏹 Archer - High agility, low health, moderate attack",
        "tank": "🛡️ Tank - High health and defense, low attack",
        "mage": "🔮 Mage - Low health, uses mana for party buffs and healing"
    }
    
    for class_name, description in classes.items():
        if st.button(description, key=f"class_{class_name}", use_container_width=True):
            p = st.session_state.game.data["player"]
            p['class'] = class_name
            stats = st.session_state.game.get_class_stats(class_name)
            
            p['health'] = stats['health']
            p['max_health'] = stats['health']
            p['attack'] = stats['attack']
            p['defense'] = stats['defense']
            p['agility'] = stats['agility']
            p['mana'] = stats['mana']
            
            st.session_state.class_selected = True
            st.session_state.room_state = get_room_type()
            st.session_state.game.save_data()
            st.rerun()

def show_menu():
    st.subheader("Welcome to the Advanced Roguelike!")
    col1, col2 = st.columns(2)
    with col1:
        if st.button("🆕 New Game", use_container_width=True):
            st.session_state.game.reset_game()
            st.session_state.game.save_data()
            st.session_state.game_started = True
            st.session_state.class_selected = False
            st.session_state.room_state = 'class_select'
            st.rerun()
    with col2:
        if st.button("▶️ Continue Game", use_container_width=True):
            st.session_state.game_started = True
            p = st.session_state.game.data["player"]
            if p['class'] is None:
                st.session_state.room_state = 'class_select'
            else:
                st.session_state.class_selected = True
                st.session_state.room_state = get_room_type()
            st.rerun()

def show_room_select():
    st.subheader("Choose Room Type")
    col1, col2, col3 = st.columns(3)
    with col1:
        if st.button("⚔️ Combat Room", use_container_width=True):
            st.session_state.room_state = 'combat'
            st.rerun()
    with col2:
        if st.button("🧠 Intelligence Room", use_container_width=True):
            st.session_state.room_state = 'intelligence'
            st.rerun()
    with col3:
        if st.button("🧩 Riddle Room", use_container_width=True):
            st.session_state.room_state = 'riddle'
            st.rerun()

def show_combat():
    if st.session_state.current_enemy is None:
        st.session_state.current_enemy = random.choice(st.session_state.game.data["enemies"]).copy()
        # Apply mage buffs at start of room
        st.session_state.game.apply_mage_buffs()
    
    enemy = st.session_state.current_enemy
    p = st.session_state.game.data["player"]
    
    st.subheader("⚔️ Combat Room")
    st.write(f"**{enemy['name']}** - Health: {enemy['health']}, Attack: {enemy['attack']}")
    
    for msg in st.session_state.combat_messages:
        st.write(msg)
    
    if st.button("🗡️ Attack"):
        st.session_state.combat_messages = []
        
        # Player and allies attack
        total_damage = st.session_state.game.get_total_party_attack()
        enemy['health'] -= total_damage
        st.session_state.combat_messages.append(f"Party deals {total_damage} damage!")
        
        if enemy['health'] <= 0:
            coins_dropped = random.randint(enemy['coin_min'], enemy['coin_max'])
            p['coins'] += coins_dropped
            st.session_state.combat_messages.append(f"{enemy['name']} defeated! You found {coins_dropped} coins!")
            st.session_state.current_enemy = None
            st.session_state.combat_messages = []
            st.session_state.available_perks = st.session_state.game.get_available_perks(p['room'])
            st.session_state.room_state = 'perk'
        else:
            # Enemy attacks - check agility for dodge
            if random.random() < p['agility']:
                st.session_state.combat_messages.append("You dodged the attack!")
            else:
                damage = enemy['attack'] * (1 - p['defense'])
                actual_damage = max(1.0, damage)
                p['health'] -= actual_damage
                st.session_state.combat_messages.append(f"{enemy['name']} deals {actual_damage:.1f} damage!")
                st.session_state.combat_messages.append(f"Health: {p['health']:.1f}/{p['max_health']:.1f}")
        
        st.session_state.game.save_data()
        st.rerun()

def show_riddle():
    if st.session_state.riddle_result is not None:
        result = st.session_state.riddle_result
        st.subheader("🧩 Riddle Room")
        
        if result['correct']:
            st.success("Correct! You gain wisdom and a reward!")
        else:
            st.error(f"Wrong! The answer was: {result['correct_answer']}")
        
        if st.button("Continue", use_container_width=True):
            st.session_state.riddle_result = None
            st.session_state.current_riddle = None
            if result['correct']:
                st.session_state.available_perks = st.session_state.game.get_available_perks(st.session_state.game.data["player"]['room'])
                st.session_state.room_state = 'perk'
            else:
                p = st.session_state.game.data["player"]
                p['room'] += 1
                st.session_state.room_state = get_room_type()
            st.session_state.game.save_data()
            st.rerun()
    else:
        if st.session_state.current_riddle is None:
            st.session_state.current_riddle = random.choice(st.session_state.game.data["riddles"])
        
        riddle = st.session_state.current_riddle
        st.subheader("🧩 Riddle Room")
        st.write(f"**Riddle:** {riddle['question']}")
        
        user_answer = st.text_input("Your answer:").lower().strip()
        
        if st.button("Submit Answer"):
            if user_answer == riddle['answer'].lower():
                st.session_state.riddle_result = {'correct': True, 'correct_answer': riddle['answer']}
            else:
                st.session_state.riddle_result = {'correct': False, 'correct_answer': riddle['answer']}
            st.rerun()

def show_ally_encounter():
    st.subheader("🤝 Ally Encounter")
    
    if 'potential_ally' not in st.session_state:
        st.session_state.potential_ally = random.choice(st.session_state.game.data["allies_pool"]).copy()
        st.session_state.potential_ally['max_health'] = st.session_state.potential_ally['health']
    
    ally = st.session_state.potential_ally
    st.write(f"You encounter **{ally['name']}** who offers to join your party!")
    st.write(f"Stats: {ally['health']} HP, {ally['attack']} ATK")
    
    col1, col2 = st.columns(2)
    with col1:
        if st.button("✅ Recruit Ally", use_container_width=True):
            st.session_state.game.data["allies"].append(ally)
            st.success(f"{ally['name']} joined your party!")
            del st.session_state.potential_ally
            p = st.session_state.game.data["player"]
            p['room'] += 1
            st.session_state.room_state = get_room_type()
            st.session_state.game.save_data()
            st.rerun()
    
    with col2:
        if st.button("❌ Continue Alone", use_container_width=True):
            del st.session_state.potential_ally
            p = st.session_state.game.data["player"]
            p['room'] += 1
            st.session_state.room_state = get_room_type()
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
            st.session_state.game.apply_mage_buffs()
            st.rerun()
    else:
        boss = st.session_state.current_boss
        st.subheader("👹 Boss Fight")
        st.write(f"**{boss['name']}** - Health: {boss['health']}, Attack: {boss['attack']}")
        
        for msg in st.session_state.boss_messages:
            st.write(msg)
        
        if st.button("⚔️ Attack Boss"):
            st.session_state.boss_messages = []
            total_damage = st.session_state.game.get_total_party_attack()
            boss['health'] -= total_damage
            st.session_state.boss_messages.append(f"Party deals {total_damage} damage!")
            
            if boss['health'] <= 0:
                coins_dropped = random.randint(boss['coin_min'], boss['coin_max'])
                p['coins'] += coins_dropped
                st.session_state.boss_messages.append(f"{boss['name']} defeated! You found {coins_dropped} coins!")
                st.session_state.current_boss = None
                st.session_state.boss_messages = []
                st.session_state.available_perks = st.session_state.game.get_available_perks(p['room'], is_boss=True)
                st.session_state.room_state = 'perk'
                st.session_state.shop_active = True
            else:
                if random.random() < p['agility']:
                    st.session_state.boss_messages.append("You dodged the boss attack!")
                else:
                    damage = boss['attack'] * (1 - p['defense'])
                    actual_damage = max(1.0, damage)
                    p['health'] -= actual_damage
                    st.session_state.boss_messages.append(f"{boss['name']} deals {actual_damage:.1f} damage!")
                    st.session_state.boss_messages.append(f"Health: {p['health']:.1f}/{p['max_health']:.1f}")
            
            st.session_state.game.save_data()
            st.rerun()

def show_superboss():
    p = st.session_state.game.data["player"]
    
    if st.session_state.current_superboss is None:
        st.subheader("💀 SUPERBOSS ROOM")
        st.warning("This is an extremely powerful enemy!")
        if st.button("⚔️ Enter Superboss Room", use_container_width=True):
            boss_index = (p['room'] // 50) - 1
            if boss_index >= len(st.session_state.game.data["superbosses"]):
                boss_index = len(st.session_state.game.data["superbosses"]) - 1
            st.session_state.current_superboss = st.session_state.game.data["superbosses"][boss_index].copy()
            st.session_state.game.apply_mage_buffs()
            st.rerun()
    else:
        superboss = st.session_state.current_superboss
        st.subheader("💀 SUPERBOSS FIGHT")
        st.write(f"**{superboss['name']}** - Health: {superboss['health']}, Attack: {superboss['attack']}")
        
        for msg in st.session_state.boss_messages:
            st.write(msg)
        
        if st.button("⚔️ Attack Superboss"):
            st.session_state.boss_messages = []
            total_damage = st.session_state.game.get_total_party_attack()
            superboss['health'] -= total_damage
            st.session_state.boss_messages.append(f"Party deals {total_damage} damage!")
            
            if superboss['health'] <= 0:
                coins_dropped = random.randint(superboss['coin_min'], superboss['coin_max'])
                p['coins'] += coins_dropped
                st.session_state.boss_messages.append(f"{superboss['name']} defeated! You found {coins_dropped} coins!")
                st.session_state.current_superboss = None
                st.session_state.boss_messages = []
                st.session_state.available_perks = st.session_state.game.get_available_perks(p['room'], is_superboss=True)
                st.session_state.room_state = 'perk'
            else:
                if random.random() < p['agility']:
                    st.session_state.boss_messages.append("You dodged the superboss attack!")
                else:
                    damage = superboss['attack'] * (1 - p['defense'])
                    actual_damage = max(1.0, damage)
                    p['health'] -= actual_damage
                    st.session_state.boss_messages.append(f"{superboss['name']} deals {actual_damage:.1f} damage!")
                    st.session_state.boss_messages.append(f"Health: {p['health']:.1f}/{p['max_health']:.1f}")
            
            st.session_state.game.save_data()
            st.rerun()

def show_perk():
    st.subheader("🎁 Choose a Perk")
    st.info("You must choose a perk before proceeding.")
    
    for i, perk in enumerate(st.session_state.available_perks):
        rarity_color = {"common": "🟢", "rare": "🔵", "unique": "🟡"}
        color = rarity_color.get(perk['rarity'], "⚪")
        
        if st.button(f"{color} {perk['name']} (+{perk['value']} {perk['type']}) [{perk['rarity']}]", key=f"perk_{i}"):
            st.session_state.game.apply_perk(perk)
            
            if perk['rarity'] == 'unique':
                st.session_state.game.data["unique_perks_obtained"].append(perk['name'])
            
            st.success(f"You gained {perk['name']}!")
            st.session_state.available_perks = None
            
            p = st.session_state.game.data["player"]
            if st.session_state.shop_active:
                st.session_state.room_state = 'shop'
                st.session_state.shop_perks = st.session_state.game.get_available_perks(p['room'])
                st.session_state.purchased_perks = []
            else:
                p['room'] += 1
                st.session_state.room_state = get_room_type()
            
            st.session_state.game.save_data()
            st.rerun()

def show_shop():
    p = st.session_state.game.data["player"]
    
    if st.session_state.shop_perks is None:
        st.session_state.shop_perks = st.session_state.game.get_available_perks(p['room'])
        st.session_state.purchased_perks = []
    
    st.subheader("🏪 Shop")
    st.write(f"Welcome to the shop! Each perk costs 8 coins.")
    st.write(f"Your coins: {p['coins']}")
    
    for i, perk in enumerate(st.session_state.shop_perks):
        rarity_color = {"common": "🟢", "rare": "🔵", "unique": "🟡"}
        color = rarity_color.get(perk['rarity'], "⚪")
        status = "SOLD" if i in st.session_state.purchased_perks else "Available"
        disabled = i in st.session_state.purchased_perks or p['coins'] < 8
        
        if st.button(f"{color} {perk['name']} (+{perk['value']} {perk['type']}) - 8 coins ({status})", 
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
                st.session_state.available_perks = st.session_state.game.get_available_perks(st.session_state.game.data["player"]['room'])
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

# Main app
init_session_state()
st.title("🗡️ Advanced Roguelike Game")

# Game over check
p = st.session_state.game.data["player"]
if st.session_state.game_started and p['health'] <= 0:
    st.error("💀 GAME OVER!")
    if st.button("Start New Game"):
        st.session_state.game.reset_game()
        st.session_state.game.save_data()
        st.session_state.room_state = 'menu'
        st.session_state.game_started = False
        st.session_state.class_selected = False
        st.rerun()
    st.stop()

# Show stats if game started and class selected
if st.session_state.game_started and st.session_state.class_selected:
    show_stats()
    st.divider()

# Route to appropriate screen
if not st.session_state.game_started or st.session_state.room_state == 'menu':
    show_menu()
elif st.session_state.room_state == 'class_select':
    show_class_selection()
elif st.session_state.room_state == 'room_select' or st.session_state.room_state == 'regular':
    show_room_select()
elif st.session_state.room_state == 'combat':
    show_combat()
elif st.session_state.room_state == 'intelligence':
    show_intelligence()
elif st.session_state.room_state == 'riddle':
    show_riddle()
elif st.session_state.room_state == 'ally':
    show_ally_encounter()
elif st.session_state.room_state == 'boss':
    show_boss()
elif st.session_state.room_state == 'superboss':
    show_superboss()
elif st.session_state.room_state == 'perk':
    show_perk()
elif st.session_state.room_state == 'shop':
    show_shop()