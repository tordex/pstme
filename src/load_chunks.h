#ifndef LOAD_CHUNKS_H
#define LOAD_CHUNKS_H

#include <memory>
#include "chunks.h"

extern std::shared_ptr<chunks> load_bookmarks_from_file(const std::string& path);

#endif // LOAD_CHUNKS_H
