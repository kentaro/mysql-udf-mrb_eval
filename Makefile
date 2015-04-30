CFLAGS = -Ivendor/mruby/include

all: build libmruby.a
	gcc -o build/mrb_eval.so mrb_eval.cpp -Ivendor/mruby/include `mysql_config --cflags` -shared vendor/mruby/build/host/lib/libmruby.a -lm && cp build/mrb_eval.so `mysql_config --plugindir`/mrb_eval.so

libmruby.a: vendor/mruby
	cd vendor/mruby && ${MAKE}

vendor/mruby:
	mkdir -p vendor
	git clone https://github.com/mruby/mruby.git vendor/mruby
	cd vendor/mruby && git reset --hard && git clean -fdx

build:
	mkdir -p build

clean:
	rm -rf vendor
	rm -rf build
