#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;
	bool loop;
	int loops;

private:
	float current_frame;
public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f), loop(true), loops(1)
	{}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if (current_frame >= frames.size()){
			current_frame = (loop) ? 0.0f : frames.size() - 1;
			--loops;
		}
		return frames[(int)current_frame];
	}

	void reset(){
		current_frame = 0.0f;
		loops = 1;
	}

	bool hasFinished(){
		return loops == 0;
	}

	SDL_Rect& GetFrame(int frame){
		return frames[frame];
	}
};