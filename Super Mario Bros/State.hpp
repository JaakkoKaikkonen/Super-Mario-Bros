#pragma once

namespace engine {

	class State {

	public:
		virtual void init() = 0;

		virtual void handleInput(const float& dt) = 0;
		virtual void update(const float& dt) = 0;
		virtual void draw() = 0;

		virtual void pause() {}
		virtual void resume() {}

	};

}
