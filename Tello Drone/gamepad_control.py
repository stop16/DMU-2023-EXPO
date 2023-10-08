import pygame

pygame.init()

joysticks = {}

def main():
    done = False
    global left_x_axis, left_y_axis, right_x_axis, right_y_axis, button
    while not done:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

            # Handle hotplugging
            if event.type == pygame.JOYDEVICEADDED:
                # This event will be generated when the program starts for every
                # joystick, filling up the list without needing to create them manually.
                joy = pygame.joystick.Joystick(event.device_index)
                joysticks[joy.get_instance_id()] = joy
                print(f"Joystick {joy.get_instance_id()} connencted")

            if event.type == pygame.JOYDEVICEREMOVED:
                del joysticks[event.instance_id]
                print(f"Joystick {event.instance_id} disconnected")
        for joystick in joysticks.values():
            left_x_axis = round(joystick.get_axis(0),2)
            left_y_axis = round(joystick.get_axis(1),2)
            right_x_axis = round(joystick.get_axis(3),2)
            right_y_axis = round(joystick.get_axis(4),2)
            button = joystick.get_button(0)