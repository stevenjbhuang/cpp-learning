BUILD_DIR  := build
CMAKE      := cmake
NINJA      := ninja
CXX_COMP   := clang++
FMT        := clang-format
TIDY       := clang-tidy

MODULE     ?= 01_fundamentals

.PHONY: all configure configure-debug build build-debug run clean format format-check tidy help

all: build

configure:
	$(CMAKE) -B $(BUILD_DIR) -G Ninja \
		-DCMAKE_CXX_COMPILER=$(CXX_COMP) \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

configure-debug:
	$(CMAKE) -B $(BUILD_DIR) -G Ninja \
		-DCMAKE_CXX_COMPILER=$(CXX_COMP) \
		-DCMAKE_BUILD_TYPE=Debug \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON

build: configure
	$(NINJA) -C $(BUILD_DIR)

build-debug: configure-debug
	$(NINJA) -C $(BUILD_DIR)

run: build
	@echo ">>> Running $(MODULE)"
	@./$(BUILD_DIR)/$(MODULE)/$(MODULE)

format:
	@find . -path ./$(BUILD_DIR) -prune -o \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print \
		| xargs $(FMT) -i --style=file
	@echo "Formatted all source files."

format-check:
	@find . -path ./$(BUILD_DIR) -prune -o \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" \) -print \
		| xargs $(FMT) --style=file --dry-run --Werror

tidy:
	@find . -path ./$(BUILD_DIR) -prune -o -name "*.cpp" -print \
		| xargs $(TIDY) -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "Removed $(BUILD_DIR)/"

help:
	@printf "\n%-22s %s\n" "Target" "Description"
	@printf "%-22s %s\n"   "------" "-----------"
	@printf "%-22s %s\n"   "build"          "Configure + build all modules (Release)"
	@printf "%-22s %s\n"   "build-debug"    "Configure + build all modules (Debug + ASan/UBSan)"
	@printf "%-22s %s\n"   "run"            "Run a module  (MODULE=<dir>, default: 01_fundamentals)"
	@printf "%-22s %s\n"   "format"         "Auto-format all sources with clang-format"
	@printf "%-22s %s\n"   "format-check"   "Verify formatting without modifying files"
	@printf "%-22s %s\n"   "tidy"           "Run clang-tidy static analysis on all sources"
	@printf "%-22s %s\n"   "clean"          "Remove the build directory"
	@printf "%-22s %s\n"   "help"           "Show this message"
	@printf "\n  Examples:\n"
	@printf "    make run MODULE=13_concurrency_basics\n"
	@printf "    make build-debug && make run MODULE=20_lock_free_programming\n\n"
