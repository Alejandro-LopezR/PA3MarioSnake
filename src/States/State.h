#pragma once

#include <string>

class State {
	public:
		State() {}
		virtual void reset() = 0;
		virtual void update() = 0;
		virtual void draw() = 0;
        virtual void keyPressed(int key) = 0;
		virtual void mousePressed(int x, int y, int button) = 0;

		bool hasFinished(){
			return finished;
		}
		std::string getNextState(){
			return nextState;
		}
		void setFinished(bool finished){
			this->finished = finished;
		}

		void setNextState(std::string nextState){
			this->nextState = nextState;
		}

		bool getIsPaused(){ return isPaused; }

		void setIsPaused(bool isPaused){ this->isPaused = isPaused;}

	private:
		std::string nextState;
		bool finished = false;
		bool isPaused = false;
};