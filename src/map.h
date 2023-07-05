#ifndef NOWHERE_MAP_H
#define NOWHERE_MAP_H

#include <stddef.h>

struct nowhere_node;

struct nowhere_map {
	size_t count;
	struct nowhere_node *head;
	struct nowhere_node *entries;
};

int nowhere_map_create(struct nowhere_map **_map, size_t _count);

struct nowhere_node *nowhere_map_put(struct nowhere_map *_map, struct nowhere_node *_node);

struct nowhere_node *nowhere_map_get(struct nowhere_map *_map, const char *_name);

void nowhere_map_print(struct nowhere_map *_map);

#endif //NOWHERE_MAP_H