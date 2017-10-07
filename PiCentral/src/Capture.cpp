#include "Capture.hpp"

Capture::Capture() : _should_run{false} {
	
}

void Capture::start(unsigned int camera) {
	_capture.open(camera);
	_should_run = true;
	run();
}

void Capture::start(std::string source_url) {
	_capture.open(source_url);
	_should_run = true;
	run();
}

void Capture::run() {
	while(_should_run) {
		_capture >> _frame;
		process(_frame);
	}
}