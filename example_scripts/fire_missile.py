import time
import cube

# Get the world
world = cube.get_game().world

for i in range(100):
	world.local_player.entity_data.action_id = 47

	# Start ~1 second into the skill so that the missiles file immediately.
	world.local_player.entity_data.action_timer = 950 

	# Wait 200 milliseconds
	time.sleep(.2)