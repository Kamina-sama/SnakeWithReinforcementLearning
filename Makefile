.PHONY: clean All

All:
	@echo "----------Building project:[ SnakeGame - Debug ]----------"
	@"$(MAKE)" -f  "SnakeGame.mk"
clean:
	@echo "----------Cleaning project:[ SnakeGame - Debug ]----------"
	@"$(MAKE)" -f  "SnakeGame.mk" clean
