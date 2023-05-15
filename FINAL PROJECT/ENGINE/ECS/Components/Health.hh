/* MANAGE HEALTH AND SCORE; MOREOVER, STORES IF THE PLAYER HAS WON */

struct HealthComponent {
    int health;
    int maxHealth;
    
    HealthComponent(int h = 1000) : health(h), maxHealth(h) {}
};

struct ScoreComponent {
    int score;
    int maxScore;
    bool win = false;

    ScoreComponent(int s = 1000): score(s),maxScore(s){}
};
