#pragma once
#include <vector>

struct Frametime
{
public:
	std::vector<float> FrameTimeQueue; // Vector that holds the frames

	uint32_t capacity = 240; // How many frames to store at a time
	void push(float frameTime)
	{
		if (FrameTimeQueue.size() >= capacity) // If we hit the limit
		{
			FrameTimeQueue.erase(FrameTimeQueue.begin()); // We clear the first element
			FrameTimeQueue.push_back(frameTime); // And we add another one over on the back
		}
		else
		{
			FrameTimeQueue.push_back(frameTime); // We push a frame if the limit is not reached
		}

	}

	float averageTime() // Calculates an average of the frames in the vector
	{
		float average = 0;
		for (int i = 0; i < FrameTimeQueue.size(); i++)
		{
			average += FrameTimeQueue[i];
		}

		return average / FrameTimeQueue.size(); // Returns the average value
	}

};