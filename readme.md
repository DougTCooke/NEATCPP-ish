# NEATCPP-ish

A working-ish neat implementation written in cpp. It can be run from the ./main file after building with make. It may need to be run a few times to find a solution.

## Training

The XORTrainer class is used to provide the goal to the network. Each network is passed to the evaluate function during the pop::evaluate call which returns that networks fitness.

## Configuring

The config.cpp file holds the configuration settings, this was going to be read from a file using this class but is currently hardcoded.
