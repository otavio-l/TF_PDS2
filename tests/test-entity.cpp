#include "doctest.h"
#include "entity.hpp"
#include "constants.hpp"

TEST_CASE("LiveEntity default constructor") {
    LiveEntity entity;
    CHECK(entity.direction.up == false);
    CHECK(entity.direction.down == false);
    CHECK(entity.direction.left == false);
    CHECK(entity.direction.right == false);
}

TEST_CASE("LiveEntity parameterized constructor") {
    sf::Texture texture;
    LiveEntity entity(texture, 50.0f, 100.0f, 10.0f, 20.0f);
    CHECK(entity.direction.up == false);
    CHECK(entity.direction.down == false);
    CHECK(entity.direction.left == false);
    CHECK(entity.direction.right == false);
    CHECK(entity.hitbox.getPosition().x == 50.0f);
    CHECK(entity.hitbox.getPosition().y == 100.0f);
    CHECK(entity.hitbox.getSize().x == 10.0f);
    CHECK(entity.hitbox.getSize().y == 20.0f);
}

TEST_CASE("PlayerEntity inheritance") {
    sf::Texture texture;
    PlayerEntity player(texture, 50.0f, 100.0f, 10.0f, 20.0f);
    CHECK(player.direction.up == false);
    CHECK(player.direction.down == false);
    CHECK(player.direction.left == false);
    CHECK(player.direction.right == false);
    CHECK(player.hitbox.getPosition().x == 50.0f);
    CHECK(player.hitbox.getPosition().y == 100.0f);
    CHECK(player.hitbox.getSize().x == 10.0f);
    CHECK(player.hitbox.getSize().y == 20.0f);
}

TEST_CASE("PlayerEntity::move()") {
    sf::Texture texture;
    PlayerEntity player(texture, 50.0f, 100.0f, 7.0f, 20.0f);

    Direction collisions { false, false, false, false };
    float velocity = static_cast<float>(constants::mainCharacterVelocity);

    // move up
    player.direction.up = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().y == 100.0f - velocity);
    player.direction.up = false;

    // right
    player.direction.right = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().x == 50.0f + velocity);
    player.direction.right = false;

    // down
    player.direction.down = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().y == 100.0f);
    player.direction.down = false;

    // left
    player.direction.left = true;
    player.move(collisions, velocity);
    CHECK(player.hitbox.getPosition().x == 50.0f);
    player.direction.left = false;
}

TEST_CASE("EnemyEntity inheritance and methods") {
    sf::Texture texture;
    EnemyEntity enemy(texture, constants::enemyPosAbsX, constants::enemyPosAbsY, 
        constants::enemyWidth, constants::enemyHeight);
    
    CHECK(enemy.direction.up == false);
    CHECK(enemy.direction.down == false);
    CHECK(enemy.direction.left == false);
    CHECK(enemy.direction.right == false);
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

TEST_CASE("EnemyEntity::move()") {
    sf::Texture texture;
    EnemyEntity enemy(texture, constants::enemyPosAbsX, constants::enemyPosAbsY, 
        constants::enemyWidth, constants::enemyHeight);

    float initialX = enemy.absX;
    float initialY = enemy.absY;

    // Move right and down
    enemy.direction.right = true;
    enemy.direction.down = true;
    enemy.move();
    CHECK(enemy.absX == initialX + constants::enemyVelocity);
    CHECK(enemy.absY == initialY + constants::enemyVelocity);
    enemy.direction.right = false;
    enemy.direction.down = false;

    // Move left and up
    enemy.direction.left = true;
    enemy.direction.up = true;
    enemy.move();
    CHECK(enemy.absX == initialX);
    CHECK(enemy.absY == initialY);
}

TEST_CASE("EnemyEntity::setFollowing()") {
    sf::Texture texture;
    EnemyEntity enemy(texture, 100.0f, 100.0f, 7.0f, 20.0f);
    LiveEntity mainCharacter(texture, 150.0f, 150.0f, 7.0f, 20.0f);

    enemy.setFollowing(mainCharacter);

    CHECK(enemy.direction.right == true);
    CHECK(enemy.direction.left == false);
    CHECK(enemy.direction.down == true);
    CHECK(enemy.direction.up == false);
}

TEST_CASE("EnemyEntity::currentScreen()") {
    sf::Texture texture;
    EnemyEntity enemy(texture, 400.0f, 300.0f, 7.0f, 20.0f);
    LiveEntity mainCharacter(texture, 390.0f, 290.0f, 7.0f, 20.0f);

    enemy.currentScreen(mainCharacter);

    CHECK(enemy.onScreen == true);
    CHECK(enemy.hitbox.getPosition().x >= 0.0f);
    CHECK(enemy.hitbox.getPosition().y >= 0.0f);
}

TEST_CASE("LiveEntity::animate()") {
    sf::Texture texture;
    LiveEntity entity(texture, 50.0f, 100.0f, 7.0f, 20.0f);

    // Test initial state (all directions false)
    entity.animate();
    CHECK(true);

    // Test w/ direction
    entity.direction.up = true;
    entity.animate();
    CHECK(true);
    entity.direction.up = false;

    entity.direction.down = true;
    entity.animate();
    CHECK(true);
    entity.direction.down = false;

    entity.direction.left = true;
    entity.animate();
    CHECK(true);
    entity.direction.left = false;

    entity.direction.right = true;
    entity.animate();
    CHECK(true);
    entity.direction.right = false;
}
