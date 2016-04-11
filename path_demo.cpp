#include <iostream>
#include <map>
#include <unordered_set>
#include "filesystem/path.h"
#include "filesystem/resolver.h"

using namespace std;
using namespace filesystem;

int main(int argc, char **argv) {
#if !defined(WIN32)
    path path1("/dir 1/dir 2/");
#else
    path path1("C:\\dir 1\\dir 2\\");
#endif
    path path2("dir 3");

    cout << path1.length() << endl;
    for (size_t i = 0; i < path1.length(); i++) {
	cout << ": " << path1[i] << endl;
    }
    cout << path1.exists() << endl;
    cout << path1 << endl;
    cout << (path1/path1.as_relative()) << endl;
    cout << (path1/path2) << endl;
    cout << (path1/path2).dirname() << endl;
    cout << (path1/path2).dirname().dirname() << endl;
    cout << (path1/path2).dirname().dirname().dirname() << endl;
    cout << (path1/path2).dirname().dirname().dirname().dirname() << endl;
    cout << path().dirname() << endl;
    cout << "some/path.ext:operator==() = " << (path("some/path.ext") == path("some/path.ext")) << endl;
    cout << "some/path.ext:operator==() (unequal) = " << (path("some/path.ext") == path("another/path.ext")) << endl;

    map<path, int> pathInts;
    pathInts[path::getcwd()] = 125;
    pathInts[path::getcwd() / "foo"] = 1337;
    cout << "map[cwd] (125) = " << pathInts[path::getcwd()] << endl;
    cout << "map[cwd/foo] (1337) = " << pathInts[path::getcwd() / "foo"] << endl;

    unordered_set<path> pathSet;
    pathSet.insert("foo/bar");
    pathSet.insert("qux/qix");
    pathSet.insert("foo/bar");
    cout << "pathSet size (2) = " << pathSet.size() << endl;

    cout << "nonexistant:exists = " << path("nonexistant").exists() << endl;
    cout << "nonexistant:is_file = " << path("nonexistant").is_file() << endl;
    cout << "nonexistant:is_directory = " << path("nonexistant").is_directory() << endl;
    cout << "nonexistant:basename = " << path("nonexistant").basename() << endl;
    cout << "nonexistant:extension = " << path("nonexistant").extension() << endl;
    cout << "filesystem/path.h:exists = " << path("filesystem/path.h").exists() << endl;
    cout << "filesystem/path.h:is_file = " << path("filesystem/path.h").is_file() << endl;
    cout << "filesystem/path.h:is_directory = " << path("filesystem/path.h").is_directory() << endl;
    cout << "filesystem/path.h:basename = " << path("filesystem/path.h").basename() << endl;
    cout << "filesystem/path.h:extension = " << path("filesystem/path.h").extension() << endl;
    cout << "a/../../foo.c:resolve = " << path("a/../../foo.c").resolve() << endl;
    if (path("filesystem/path.h").exists()) {
        cout << "filesystem/path.h:make_absolute = " << path("filesystem/path.h").make_absolute() << endl;
    }
    cout << "filesystem/path.h:dirname = " << path("filesystem/path.h").dirname() << endl;
    cout << "filesystem/path.h:basename = " << path("filesystem/path.h").basename() << endl;
    cout << "filesystem/path.h:resolve = " << path("filesystem/path.h").resolve() << endl;
    cout << "/a/b/c/../../d/e/foo/../././././bar.h:resolve = " << path("/a/b/c/../../d/e/foo/../././././bar.h").resolve() << endl;
    cout << "filesystem/../path.h:resolve = " << path("filesystem/../path.h").resolve() << endl;
    cout << "filesystem/path.h:resolve /a/b/c = " << path("/a/b/c").resolve("filesystem/path.h") << endl;
    cout << "../filesystem/path.h:resolve /a/b/c = " << path("/a/b/c").resolve("../filesystem/path.h") << endl;
    cout << "../filesystem/path.h:resolve /a/b/../c = " << path("/a/b/../c").resolve("../filesystem/path.h") << endl;
    cout << "../filesystem:exists = " << path("../filesystem").exists() << endl;
    cout << "../filesystem:is_file = " << path("../filesystem").is_file() << endl;
    cout << "../filesystem:is_directory = " << path("../filesystem").is_directory() << endl;
    cout << "../filesystem:extension = " << path("../filesystem").extension() << endl;
    cout << "../filesystem:basename = " << path("../filesystem").basename() << endl;
    cout << "../filesystem/path.h:resolve = " << path("../filesystem/path.h").resolve() << endl;
    if (path("../filesystem").exists()) {
        cout << "../filesystem:make_absolute = " << path("../filesystem").make_absolute() << endl;
    }
    cout << "../../a/b/c/../d:resolve = " << path("../../a/b/c/../d").resolve() << endl;
    cout << "/../../a/b/c/../d:resolve = " << path("/../../a/b/c/../d").resolve() << endl;

    cout << "resolve(filesystem/path.h) = " << resolver().resolve("filesystem/path.h") << endl;
    cout << "resolve(nonexistant) = " << resolver().resolve("nonexistant") << endl;
    return 0;
}
