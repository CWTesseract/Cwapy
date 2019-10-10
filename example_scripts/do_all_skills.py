import time
import cube

# Get the world
world = cube.get_game().world

# Do all skills/actions from id 0 -> 100.
for i in range(100):
	print("Doing skill ID:{}".format(i))
	world.local_player.entity_data.action_id = i
	world.local_player.entity_data.action_timer = 0

	# Give each one two seconds.
	time.sleep(2)
	