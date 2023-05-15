struct HealthComponent {
    int health;
    int maxHealth;
    
    HealthComponent(int h = 100) : health(h), maxHealth(h) {}
};

struct ScoreComponent {
    int score;
    int maxScore;
    bool win = false;

    ScoreComponent(int s = 1000): score(s),maxScore(s){}
};
