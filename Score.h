#ifndef SCORE_H
#define SCORE_H

class Score {
private:
    int score;
public:
    Score() : score(0) {}
    void increase(int amount) { 
      score += amount; 
    }
    int getScore() const { 
      return score; 
    }
};

#endif 