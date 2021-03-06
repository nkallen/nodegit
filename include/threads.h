/*
 * Copyright 2011, Tim Branyen @tbranyen <tim@tabdeveloper.com>
 * @author Michael Robinson @codeofinterest <mike@pagesofinterest.net>
 *
 * Dual licensed under the MIT and GPL licenses.
 */

#include <v8.h>
#include <node.h>

#include "git2.h"

using namespace node;
using namespace v8;

/**
 * Class wrapper for libgit2 git_threads_*
 */
class GitThreads : public ObjectWrap {
  public:
    /**
     * v8::FunctionTemplate used to create Node.js constructor
     */
    static Persistent<Function> constructor_template;

    static void Initialize (Handle<v8::Object> target);

    /**
     * Calls git_threads_init synchronously. This is called one time
     * on initialization, and is required for libgit2 to run correctly.
     */
    static Handle<Value> Init(const Arguments& args);

  protected:

    GitThreads() {}
    ~GitThreads() {}

    static Handle<Value> New(const Arguments& args);

};
