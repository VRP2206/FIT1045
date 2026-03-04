class BankAccount:
    def __init__(self, name="Unknown", balance=0):
        """Initialize bank account with name and balance"""
        self.name = name
        self._balance = balance
    
    def print(self):
        """Print account name and balance"""
        print(f"{self.name}: ${self._balance}")
    
    def deposit(self, amount):
        """Deposit money into account"""
        self._balance += amount
        print(f"${amount} has been deposited")
    
    def withdraw(self, amount):
        """Withdraw money from account"""
        if self._balance >= amount:
            self._balance -= amount
            print(f"${amount} has been withdraw")
        else:
            print("Not enought money...")

class Transaction:
    def __init__(self, account, amount):
        """Initialize transaction with account and amount"""
        self._performed = False
        self._succeeded = False
        self.amount = amount
        self.account = account
    
    def perform(self):
        """Perform the transaction"""
        raise NotImplementedError
    
    def was_performed(self):
        """Check if transaction was performed"""
        return self._performed
    
    def was_successful(self):
        """Check if transaction was successful"""
        return self._succeeded

class WithdrawTransaction(Transaction):
    def perform(self):
        """Perform withdrawal transaction"""
        if self._performed:
            raise Exception("Transaction already performed")
        
        try:
            self.account.withdraw(self.amount)
            self._succeeded = True
        except Exception as e:
            print(f"Transaction failed: {e}")
            self._succeeded = False
        self._performed = True

class DepositTransaction(Transaction):
    def perform(self):
        """Perform deposit transaction"""
        if self._performed:
            raise Exception("Transaction already performed")
        
        try:
            self.account.deposit(self.amount)
            self._succeeded = True
        except Exception as e:
            print(f"Transaction failed {e}")
            self._succeeded = False
        self._performed = True

if __name__ == "__main__":
    acc = BankAccount("sam", 90125)
    
    acc.print()
    
    test = WithdrawTransaction(acc, 1000)
    test.perform()
    
    if test.was_successful():
        print("Transaction successful!")
    else:
        print("Transaction failed")
    
    acc.print()
    
    test = DepositTransaction(acc, 2000)
    test.perform()
    
    if test.was_successful():
        print("Transaction successful!")
    else:
        print("Transaction failed")
    
    acc.print()