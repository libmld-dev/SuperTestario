extends Control

# Called when the node enters the scene tree for the first time.
func _ready():
	var btnBack = $btnBack
	btnBack.pressed.connect(self.back_pressed)
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
func back_pressed():
	print("Back!")
	var scene_main_menu = load("res://scenes/main_menu.tscn").instantiate()
	get_tree().root.add_child(scene_main_menu)
	get_node("/root/ui").queue_free()
	get_node("/root/world001").queue_free()
	pass
