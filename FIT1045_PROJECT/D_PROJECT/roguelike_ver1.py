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
            "player": {"health": 10, "max_health": 10, "attack": 1, "defense": 0, "room": 1},
            "enemies": [
                {"name": "Goblin", "health": 5, "attack": 1},
                {"name": "Orc", "health": 8, "attack": 2},
                {"name": "Skeleton", "health": 6, "attack": 1},
                {"name": "Wolf", "health": 4, "attack": 2}
            ],
            "bosses": [
                {"name": "Troll King", "health": 25, "attack": 4},
                {"name": "Dragon", "health": 40, "attack": 6},
                {"name": "Lich", "health": 35, "attack": 5}
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
    
    def display_stats(self):
        p = self.data["player"]
        print(f"\n--- Player Stats ---")
        print(f"Room: {p['room']}")
        print(f"Health: {p['health']}/{p['max_health']}")
        print(f"Attack: {p['attack']}")
        print(f"Defense: {p['defense']:.1f}")
    
    def combat_room(self):
        enemy = random.choice(self.data["enemies"]).copy()
        print(f"\nA {enemy['name']} appears!")
        print(f"{enemy['name']} - Health: {enemy['health']}, Attack: {enemy['attack']}")
        
        while enemy['health'] > 0 and self.data["player"]['health'] > 0:
            input("\nPress Enter to attack...")
            
            # Player attacks
            enemy['health'] -= self.data["player"]['attack']
            print(f"You deal {self.data['player']['attack']} damage!")
            
            if enemy['health'] <= 0:
                print(f"{enemy['name']} defeated!")
                return True
            
            # Enemy attacks
            damage = max(1, int(enemy['attack'] * (1 - self.data["player"]['defense'])))
            self.data["player"]['health'] -= damage
            print(f"{enemy['name']} deals {damage} damage!")
            
            if self.data["player"]['health'] <= 0:
                print("You died!")
                return False
        
        return True
    
    def boss_room(self):
        boss_index = (self.data["player"]['room'] // 10) - 1
        if boss_index >= len(self.data["bosses"]):
            boss_index = len(self.data["bosses"]) - 1
        
        boss = self.data["bosses"][boss_index].copy()
        print(f"\n*** BOSS ROOM ***")
        print(f"The {boss['name']} emerges!")
        print(f"{boss['name']} - Health: {boss['health']}, Attack: {boss['attack']}")
        
        while boss['health'] > 0 and self.data["player"]['health'] > 0:
            input("\nPress Enter to attack...")
            
            # Player attacks
            boss['health'] -= self.data["player"]['attack']
            print(f"You deal {self.data['player']['attack']} damage!")
            
            if boss['health'] <= 0:
                print(f"{boss['name']} defeated!")
                return True
            
            # Boss attacks
            damage = max(1, int(boss['attack'] * (1 - self.data["player"]['defense'])))
            self.data["player"]['health'] -= damage
            print(f"{boss['name']} deals {damage} damage!")
            
            if self.data["player"]['health'] <= 0:
                print("You died!")
                return False
        
        return True
    
    def intelligence_room(self):
        a = random.randint(1, 20)
        b = random.randint(1, 20)
        operation = random.choice(['+', '-', '*'])
        
        if operation == '+':
            answer = a + b
        elif operation == '-':
            answer = a - b
        else:
            answer = a * b
        
        print(f"\n--- Intelligence Room ---")
        print(f"Solve: {a} {operation} {b} = ?")
        
        try:
            user_answer = int(input("Your answer: "))
            if user_answer == answer:
                print("Correct! You gain wisdom.")
                return True
            else:
                print(f"Wrong! The answer was {answer}.")
                damage = random.randint(1, 3)
                self.data["player"]['health'] -= damage
                print(f"You take {damage} damage from confusion!")
                return self.data["player"]['health'] > 0
        except ValueError:
            print("Invalid input! You take damage from confusion!")
            self.data["player"]['health'] -= 2
            return self.data["player"]['health'] > 0
    
    def choose_perk(self):
        available_perks = random.sample(self.data["perks"], 3)
        print(f"\n--- Choose a Perk ---")
        
        for i, perk in enumerate(available_perks, 1):
            print(f"{i}. {perk['name']} (+{perk['value']} {perk['type']})")
        
        try:
            choice = int(input("Choose (1-3): ")) - 1
            if 0 <= choice < 3:
                perk = available_perks[choice]
                self.apply_perk(perk)
                print(f"You gained {perk['name']}!")
            else:
                print("Invalid choice! No perk gained.")
        except ValueError:
            print("Invalid input! No perk gained.")
    
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
    
    def play(self):
        print("=== ROGUELIKE GAME ===")
        print("1. Continue Game")
        print("2. New Game")
        
        choice = input("Choose (1-2): ")
        if choice == '2':
            self.reset_game()
        
        while self.data["player"]['health'] > 0:
            self.display_stats()
            
            if self.data["player"]['room'] % 10 == 0:
                # Boss room
                if not self.boss_room():
                    break
            else:
                # Regular room
                room_type = random.choice(['combat', 'intelligence'])
                if room_type == 'combat':
                    if not self.combat_room():
                        break
                else:
                    if not self.intelligence_room():
                        break
            
            self.choose_perk()
            self.data["player"]['room'] += 1
            self.save_data()
            print("\n------------------")
        
        if self.data["player"]['health'] <= 0:
            print("\nGAME OVER!")
            self.reset_game()
            self.save_data()

if __name__ == "__main__":
    game = RoguelikeGame()
    game.play()