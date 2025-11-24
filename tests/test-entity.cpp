#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "entity.hpp"
#include "constants.hpp"

TEST_CASE("LiveEntity default constructor") {
    LiveEntity entity;
    CHECK(entity.direction.up == false);
    CHECK(entity.direction.down == false);
    CHECK(entity.direction.left == false);
    CHECK(entity.direction.right == false);
    CHECK(entity.animateCounter == 0);
}

TEST_CASE("LiveEntity parameterized constructor") {
    sf::Texture texture;
    LiveEntity entity(texture, 50.0f, 100.0f, 10.0f, 20.0f);
    CHECK(entity.direction.up == false);
    CHECK(entity.direction.down == false);
    CHECK(entity.direction.left == false);
    CHECK(entity.direction.right == false);
    CHECK(entity.animateCounter == 0);
    CHECK(entity.hitbox.getPosition().x == 100.0f);
    CHECK(entity.hitbox.getPosition().y == 80.0f);
    CHECK(entity.hitbox.getSize().x == 10.0f);
    CHECK(entity.hitbox.getSize().y == 20.0f);
}

TEST_CASE("LiveEntity::animate()") {
    sf::Texture texture;
    LiveEntity entity(texture, 50.0f, 100.0f, 10.0f, 20.0f);

    // Initial state
    entity.animate();
    CHECK(entity.animateCounter == 0);

    // Simulate movement
    entity.direction.down = true;
    for (int i = 0; i < 15; ++i) {
        entity.animate();
    }
    CHECK(entity.animateCounter == 15 % (constants::fps / 2));

    entity.direction.down = false;
    entity.direction.up = true;
    for (int i = 0; i < 10; ++i) {
        entity.animate();
    }
    CHECK(entity.animateCounter == (15 + 10) % (constants::fps / 2));
}

TEST_CASE("PlayerEntity inheritance") {
    sf::Texture texture;
    PlayerEntity player(texture, 50.0f, 100.0f, 10.0f, 20.0f);
    CHECK(player.direction.up == false);
    CHECK(player.direction.down == false);
    CHECK(player.direction.left == false);
    CHECK(player.direction.right == false);
    CHECK(player.animateCounter == 0);
    CHECK(player.hitbox.getPosition().x == 100.0f);
    CHECK(player.hitbox.getPosition().y == 80.0f);
    CHECK(player.hitbox.getSize().x == 10.0f);
    CHECK(player.hitbox.getSize().y == 20.0f);
}

TEST_CASE("PlayerEntity::move()") {
    sf::Texture texture;
    PlayerEntity player(texture, 50.0f, 100.0f, 10.0f, 20.0f);

    Direction collisions { false, false, false, false };
    float velocity = static_cast<float>(constants::mainCharacterVelocity);

    // move up
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().y == 80.0f - velocity);

    // move down
    player.direction.up = false;
    player.direction.down = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().y == 80.0f);

    // move left
    player.direction.down = false;
    player.direction.left = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().x == 100.0f - velocity);

    // move right
    player.direction.left = false;
    player.direction.right = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().x == 100.0f);
}

TEST_CASE("EnemyEntity inheritance and methods") {
    sf::Texture texture;
    EnemyEntity enemy(texture, constants::enemyPosAbsX, constants::enemyPosAbsY, 
        constants::enemyWidth, constants::enemyHeight);
    
    CHECK(enemy.direction.up == false);
    CHECK(enemy.direction.down == false);
    CHECK(enemy.direction.left == false);
    CHECK(enemy.direction.right == false);
    CHECK(enemy.animateCounter == 0);
    CHECK(enemy.hitbox.getPosition().x == constants::enemyPosAbsX);
    CHECK(enemy.hitbox.getPosition().y == constants::enemyPosAbsY);
    CHECK(enemy.hitbox.getSize().x == constants::enemyWidth);
    CHECK(enemy.hitbox.getSize().y == constants::enemyHeight);

    LiveEntity mainCharacter(texture, 50.0f, 100.0f, 10.0f, 20.0f);
    enemy.setFollowing(mainCharacter);

    if (mainCharacter.absX > enemy.absX) {
        CHECK(enemy.direction.right == true);
        CHECK(enemy.direction.left == false);
    } else if (mainCharacter.absX < enemy.absX) {
        CHECK(enemy.direction.left == true);
        CHECK(enemy.direction.right == false);
    }

    if (mainCharacter.absY > enemy.absY) {
        CHECK(enemy.direction.down == true);
        CHECK(enemy.direction.up == false);
    } else if (mainCharacter.absY < enemy.absY) {
        CHECK(enemy.direction.up == true);
        CHECK(enemy.direction.down == false);
    }
}
