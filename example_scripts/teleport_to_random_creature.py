import random
import cube

# Get the world
world = cube.get_game().world

# Get all of the creatures that aren't the local player.
creatures = [c for c in world.creatures_list if c != world.local_player]

# Choose a random creature from the list and teleport to them.
world.local_player.entity_data.position = random.choice(creatures).entity_data.position