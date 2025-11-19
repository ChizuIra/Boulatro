#pragma once
#include "./screen.hpp"
#include "./def.hpp"

class ShopScreen : public Screen {
    private:
	int _remaining_ticks;
    public:
        ShopScreen();
	void draw() override;
	bool should_change() override;
	void reset_screen() override;
	size_t switch_to() override;
	void kill_screen() override;
};
