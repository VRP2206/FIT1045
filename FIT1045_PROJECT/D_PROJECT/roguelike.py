import json
import random

class text_format:
    # Text colors
    BLACK   = '\033[30m'
    RED     = '\033[31m'
    GREEN   = '\033[32m'
    YELLOW  = '\033[33m'
    BLUE    = '\033[34m'
    MAGENTA = '\033[35m'
    CYAN    = '\033[36m'
    WHITE   = '\033[37m'

    # Bright text colors
    BRIGHT_BLACK   = '\033[90m'
    BRIGHT_RED     = '\033[91m'
    BRIGHT_GREEN   = '\033[92m'
    BRIGHT_YELLOW  = '\033[93m'
    BRIGHT_BLUE    = '\033[94m'
    BRIGHT_MAGENTA = '\033[95m'
    BRIGHT_CYAN    = '\033[96m'
    BRIGHT_WHITE   = '\033[97m'

    # Background colors
    BG_BLACK   = '\033[40m'
    BG_RED     = '\033[41m'
    BG_GREEN   = '\033[42m'
    BG_YELLOW  = '\033[43m'
    BG_BLUE    = '\033[44m'
    BG_MAGENTA = '\033[45m'
    BG_CYAN    = '\033[46m'
    BG_WHITE   = '\033[47m'

    # Bright background colors
    BG_BRIGHT_BLACK   = '\033[100m'
    BG_BRIGHT_RED     = '\033[101m'
    BG_BRIGHT_GREEN   = '\033[102m'
    BG_BRIGHT_YELLOW  = '\033[103m'
    BG_BRIGHT_BLUE    = '\033[104m'
    BG_BRIGHT_MAGENTA = '\033[105m'
    BG_BRIGHT_CYAN    = '\033[106m'
    BG_BRIGHT_WHITE   = '\033[107m'

    # Text styles
    RESET     = '\033[0m'   # Reset all
    BOLD      = '\033[1m'
    DIM       = '\033[2m'
    ITALIC    = '\033[3m'
    UNDERLINE = '\033[4m'
    BLINK     = '\033[5m'
    REVERSE   = '\033[7m'   
    HIDDEN    = '\033[8m'
    STRIKETHROUGH = '\033[9m'

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
            "player": {"health": 10, "max_health": 10, "attack": 1, "defense": 0, "room": 1, "coins": 0},
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
    
    def display_stats(self):
        p = self.data["player"]
        print(f"\n{text_format.BRIGHT_CYAN}------Player Stats------{text_format.RESET}")
        space_box(f"Health: {p['health']:.2f}/{p['max_health']:.2f}")
        space_box(f"Attack: {p['attack']}")
        space_box(f"Defense: {p['defense']:.2f}")
        space_box(f"Coins: {p['coins']}")
        print(f"{text_format.BRIGHT_CYAN}------------------------{text_format.RESET}")
    
    def combat_room(self):
        enemy = random.choice(self.data["enemies"]).copy()
        print(f"\n{text_format.YELLOW}A {enemy['name']} appears!{text_format.RESET}")
        print(f"{enemy['name']} - Health: {enemy['health']}, Attack: {enemy['attack']}")
        
        while enemy['health'] > 0 and self.data["player"]['health'] > 0:
            input("\nPress Enter to attack...")
            
            # Player attacks
            enemy['health'] -= self.data["player"]['attack']
            print(f"You deal {self.data['player']['attack']} damage!")
            
            if enemy['health'] <= 0:
                coins_dropped = random.randint(enemy['coin_min'], enemy['coin_max'])
                self.data["player"]['coins'] += coins_dropped
                print(f"{text_format.GREEN}{enemy['name']} defeated! You found {coins_dropped} coins!{text_format.RESET}")
                return True
            
            # Enemy attacks
            damage = max(1, enemy['attack'] * (1 - self.data["player"]['defense']))
            self.data["player"]['health'] -= damage
            print(f"{enemy['name']} deals {damage:.2f} damage! | Health: {self.data['player']['health']:.2f}/{self.data['player']['max_health']:.2f}")
            
            if self.data["player"]['health'] <= 0:
                print("You died!")
                return False
        
        return True
    
    def boss_room(self):
        boss_index = (self.data["player"]['room'] // 10) - 1
        if boss_index >= len(self.data["bosses"]):
            boss_index = len(self.data["bosses"]) - 1
        
        boss = self.data["bosses"][boss_index].copy()
        print(f"\n{text_format.RED}*** BOSS ROOM ***{text_format.RESET}")
        print(f"{text_format.BRIGHT_RED}The {boss['name']} emerges!{text_format.RESET}")
        print(f"{boss['name']} - Health: {boss['health']}, Attack: {boss['attack']}")
        
        while boss['health'] > 0 and self.data["player"]['health'] > 0:
            input("\nPress Enter to attack...")
            
            # Player attacks
            boss['health'] -= self.data["player"]['attack']
            print(f"You deal {self.data['player']['attack']} damage!")
            
            if boss['health'] <= 0:
                coins_dropped = random.randint(boss['coin_min'], boss['coin_max'])
                self.data["player"]['coins'] += coins_dropped
                print(f"{text_format.GREEN}{boss['name']} defeated! You found {coins_dropped} coins!{text_format.RESET}")
                return True
            
            # Boss attacks
            damage = max(1, boss['attack'] * (1 - self.data["player"]['defense']))
            self.data["player"]['health'] -= damage
            print(f"{boss['name']} deals {damage:.2f} damage! | Health: {self.data['player']['health']:.2f}/{self.data['player']['max_health']:.2f}")
            
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
        
        print(f"\n{text_format.MAGENTA}--- Intelligence Room ---{text_format.RESET}")
        print(f"Solve: {a} {operation} {b} = ?")
        
        try:
            user_answer = int(input("Your answer: "))
            if user_answer == answer:
                print(f"{text_format.GREEN}Correct!{text_format.RESET}")
                return True
            else:
                print(f"{text_format.RED}Wrong! The answer was {answer}.{text_format.RESET}")
                damage = random.randint(1, 3)
                self.data["player"]['health'] -= damage
                print(f"You take {damage} damage from confusion!")
                return self.data["player"]['health'] > 0
        except ValueError:
            print(f"{text_format.RED}Invalid input! You take damage from confusion!{text_format.RESET}")
            self.data["player"]['health'] -= 2
            return self.data["player"]['health'] > 0
    
    def shop_room(self):
        available_perks = random.sample(self.data["perks"], 3)
        perk_price = 8
        purchased_perks = []
        
        while True:
            print(f"\n{text_format.CYAN}*** SHOP ***{text_format.RESET}")
            print(f"Welcome to the shop! Each perk costs {perk_price} coins.")
            print(f"Your coins: {self.data['player']['coins']}")
            print(f"\n-------Available Perks--------")
            print(f"|{" " * 28}|")
            for i, perk in enumerate(available_perks, 1):
                status = "SOLD" if i-1 in purchased_perks else "Available"
                if status == "SOLD":
                    print(f"|  -----{text_format.DIM}Perk {i} ({status}){text_format.RESET}------  |")
                    space_box(f"Name: {perk['name']}", True,True)
                    space_box(f"Type: {perk['type']}", True,True)
                    space_box(f"Value: {perk['value']}", True,True)
                    space_box(f"Price: {perk_price} coins", True,True)
                    print(f"|  {'-' *24}  |")
                    print(f"|{" " * 28}|")

                else:    
                    print(f"|  ---Perk {i} ({status})---  |")
                    space_box(f"Name: {perk['name']}", True)
                    space_box(f"Type: {perk['type']}", True)
                    space_box(f"Value: {perk['value']}", True)
                    space_box(f"Price: {perk_price} coins", True)
                    print(f"|  {'-' *24}  |")
                    print(f"|{" " * 28}|")
            print(f"-" *30)
            
            try:
                choice = int(input("Choose (1-3) or 0 to leave shop: "))
                if choice == 0:
                    print("You leave the shop.")
                    break
                elif 1 <= choice <= 3:
                    perk_index = choice - 1
                    if perk_index in purchased_perks:
                        print("You already bought this perk!")
                    elif self.data['player']['coins'] >= perk_price:
                        perk = available_perks[perk_index]
                        self.data['player']['coins'] -= perk_price
                        self.apply_perk(perk)
                        purchased_perks.append(perk_index)
                        print(f"You bought {perk['name']}!")
                        
                        if len(purchased_perks) == 3:
                            print("You bought all available perks!")
                            break
                    else:
                        print("Not enough coins!")
                else:
                    print("Invalid choice!")
            except ValueError:
                print("Invalid input!")
    
    def choose_perk(self):
        available_perks = random.sample(self.data["perks"], 3)
        print(f"\n--------Choose a Perk---------")
        print(f"|{" " * 28}|")
        for i, perk in enumerate(available_perks, 1):
            print(f"|  --------Perk {i}----------  |")
            space_box(f"Name: {perk['name']}", True)
            space_box(f"Type: {perk['type']}", True)
            space_box(f"Value: {perk['value']}", True)
            print(f"|  {"-" *24}  |")
            print(f"|{" " * 28}|")
        print(f"-" *30)
        
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
        print(f"{text_format.BOLD}{text_format.ITALIC}{text_format.BLINK}{text_format.UNDERLINE}=== ROGUELIKE GAME ==={text_format.RESET}")
        print("1. Continue Game")
        print("2. New Game")
        
        choice = input("Choose (1-2): ")
        if choice == '2':
            self.reset_game()
        
        while self.data["player"]['health'] > 0:
            self.display_stats()
            print(f"\n{text_format.YELLOW}------------------------------------------------------ room {self.data['player']['room']} -----------------------------------------------------{text_format.RESET}")
            
            # Check for shop rooms (after room 3 and after boss rooms)
            if self.data["player"]['room'] == 4 or (self.data["player"]['room'] > 10 and (self.data["player"]['room'] - 1) % 10 == 0):
                self.shop_room()
            elif self.data["player"]['room'] % 10 == 0:
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
            
            # Only give free perks for non-shop rooms
            if not (self.data["player"]['room'] == 4 or (self.data["player"]['room'] > 10 and (self.data["player"]['room'] - 1) % 10 == 0)):
                print(f"\n{text_format.BRIGHT_GREEN}------------------------------------------------- room {self.data['player']['room']} CONQUERED ------------------------------------------------{text_format.RESET}")
                self.choose_perk()
            
            self.data["player"]['room'] += 1
            self.save_data()
        
        if self.data["player"]['health'] <= 0:
            print(f"\n{text_format.RED}GAME OVER!{text_format.RESET}")
            self.reset_game()
            self.save_data()

def space_box(to_print, perks=False, sold = False):
    space = 21 - len(to_print)
    spa = " " * space
    if perks:
        if sold:
            print(f"|  |{text_format.DIM} {to_print}{spa}{text_format.RESET}|  |")
        else:
            print(f"|  |{text_format.REVERSE} {to_print}{spa}{text_format.RESET}|  |")
    else:
        print(f"{text_format.BLUE}| {to_print}{spa}|{text_format.RESET}")

if __name__ == "__main__":
    game = RoguelikeGame()
    game.play()