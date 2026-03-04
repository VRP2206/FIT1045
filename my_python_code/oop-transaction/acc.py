class Account:
    def __init__(self, name="Unknown", balance=0):
        self.name = name
        self.__balance = balance
    
    def deposit(self, amount):
        if amount > 0:
            self.__balance += amount
    
    def withdraw(self, amount):
        if amount > 0 and self.__balance >= amount:
            self.__balance -= amount
    
    def print(self):
        print(f"{self.name}: {self.__balance} cents")
    
    def get_balance(self):
        return self.__balance

if __name__ == "__main__":
    acc1 = Account("Alice", 5000)
    acc2 = Account("Bob", 3000)
    acc3 = Account()
    
    acc1.print()
    acc2.print()
    acc3.print()
    
    acc1.deposit(1000)
    acc1.withdraw(500)
    acc1.print()
    
    print(f"Alice's balance: {acc1.get_balance()} cents")