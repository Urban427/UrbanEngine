#include "ECS.h"
/*

struct Player
{
	int health;
	float speed;
	float runspeed;
	float jumpPower;
};

struct Enemy
{
	int health;
	float speed;
	float runspeed;
};


int main()
{
	ECS ecs;
	
	
	size_t playerID = ecs.AddEntity();
	Player* pl = ecs.AddComponent<Player>(playerID);
	Player* ul = ecs.GetComponent<Player>(playerID);
	pl->health = 100;
	pl->speed = 5;
	pl->runspeed = 12;
	pl->jumpPower = 3;
	printf("%d =? %d: %d\n", pl, ul, ul == pl);
	printf("health: %d\nspeed: %f\nrunspeed: %f\njumpPower: %f\n", pl->health, pl->speed, pl->runspeed, pl->jumpPower);
	
	size_t enemtID  = ecs.AddEntity();
	Player*  en = ecs.AddComponent<Player>(enemtID);
	Player*  un = ecs.GetComponent<Player>(enemtID);
	ul = ecs.GetComponent<Player>(playerID);
	en->health = 100;
	en->speed = 5;
	en->runspeed = 12;
	printf("%d =? %d: %d\n", ul, un, un == en);
	printf("health: %d\nspeed: %f\nrunspeed: %f\njumpPower: %f\n", ul->health, ul->speed, ul->runspeed, ul->jumpPower);
	
	printf("ecs entities number = %d\n", ecs.entities.size());
	printf("ecs  pools   number = %d\n", ecs.pools.size());
	
	return 0;
}*/