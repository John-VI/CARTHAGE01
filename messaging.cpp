// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "messaging.h"

#include "clktex.h"

#include <stdexcept>

#define FONTHEI 16

messages::messages(clk::window &window, clk::sprite &fontface, devlevel level) : win(window), font(fontface), level(level) { }

void messages::push(message msg) {
	queue.push_back(msg);
	if (queue.size() > msgcap) {
		queue.pop_front();
	}
}

void messages::draw() {
	int rows = win.getviewport(vports::MESSAGES).h / FONTHEI;
	for (int i = queue.size() - 1; i >= 0; i--) {
		try {
  font.drawstring(vports::MESSAGES, 0, (rows - i) * FONTHEI, queue.at(i).text);
		  } catch (std::out_of_range) {
		  return;
		  }
		  }
		  }

