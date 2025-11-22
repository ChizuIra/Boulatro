#pragma once

#include <cstddef>
 
class Screen {
    public:
	virtual void 	draw() = 0;
	virtual bool 	should_change() = 0;
	virtual void 	reset_screen() = 0;
	virtual void 	kill_screen() = 0;
	virtual	size_t	switch_to() = 0 ;
};
