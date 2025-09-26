default: help

# You can change these variables if you want to use a different compiler or debugger
CC = clang

all: test

check: ## Check prerequisites
	@which $(CC) > /dev/null && echo "SUCCESS: $(CC) is installed" || echo "ERROR: $(CC) not found, please install clang"

build-dir: ## Create build directory
	if [ ! -d build ]; then mkdir build; fi

build-test: build-dir ## Build test
	$(CC) -Wall -O0 -g -o build/test vec_test.c

test: build-test ## Run test.c
	./build/test

help:  ## Display this help
	@awk 'BEGIN {FS = ":.*##"; printf "\nUsage:\n  make \033[36m\033[0m\n"} /^[a-zA-Z_-]+:.*?##/ { printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2 } /^##@/ { printf "\n\033[1m%s\033[0m\n", substr($$0, 5) } ' $(MAKEFILE_LIST)