from abc import ABC, abstractmethod

class EntityEffect(ABC):
    @abstractmethod
    def perform(self, entity):
        pass