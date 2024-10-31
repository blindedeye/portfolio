PYFILE = weather_app.py

.PHONY: run
run: clean run-program

.phony: run-program
run-program:
	@echo "Starting program"
	@python3 ${PYFILE}

.phony: clean
clean:
	@echo "Cleaning dirs"
	@rm -rf `find . -type d -name __pycache__`
