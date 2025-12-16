# === Compilador y flags ===
CC       = gcc
CFLAGS   = -Wall -std=gnu17 -Iinclude -MMD -MP $(shell sdl2-config --cflags)
LDFLAGS  = $(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image 

# === Directorios ===
SRC_DIRS = src
OBJ_DIR  = build

# === Archivos fuente ===
SRC      = $(foreach dir,$(SRC_DIRS),$(shell find $(dir) -name "*.c"))
OBJ      = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))
DEP      = $(OBJ:.o=.d)

# === Ejecutable ===
TARGET   = granji 

# === Regla principal ===
all: $(TARGET)

# === Linkeo final ===
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

# === Regla genérica para compilar cualquier .c ===
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Crear carpeta build si no existe ===
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# === Limpieza ===
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# === Incluir dependencias automáticas ===
-include $(DEP)

.PHONY: all clean

