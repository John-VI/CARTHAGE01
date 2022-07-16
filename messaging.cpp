// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "messaging.h"

messages::messages(const clk::window &window, const clk::sprite &fontface, devlevel level) : win(window), font(fontface), level(level) { }

void messages::push(message msg) {
	queue.push_back(msg);
}

void messages::draw() {

