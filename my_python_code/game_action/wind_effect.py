from entity_effect import EntityEffect

class WindEffect(EntityEffect):
    def __init__(self, wind_x=0.5, wind_y=0.2):
        self.wind_x = wind_x
        self.wind_y = wind_y
    
    def perform(self, entity):
        entity.x += self.wind_x
        entity.y += self.wind_y