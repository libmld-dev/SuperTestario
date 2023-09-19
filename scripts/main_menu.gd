extends Control

# Called when the node enters the scene tree for the first time.
func _ready():
	$btnExit.pressed.connect(self.exit_pressed)
	$btnStart.pressed.connect(self.start_pressed)
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass

var scene_ui = preload("res://scenes/ui.tscn").instantiate()
var scene_world = preload("res://scenes/world001.tscn").instantiate()
func start_pressed():
	print("Start!")
	get_tree().root.add_child(scene_ui)
	get_tree().root.add_child(scene_world)
	get_node("/root/MainMenu").queue_free()
	pass

func exit_pressed():
	get_tree().quit()
	pass
