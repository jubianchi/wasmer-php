ALL_SOURCES := src/*.c src/*.h src/api/*.c src/api/*.h src/api/types/*.c src/api/objects/*.c

.SILENT: format
format: replacements.xml
	[ $(shell cat replacements.xml | grep -c "<replacement") -gt 0 ] && exit 1

.SILENT: lint
lint: fixes.yml
	[ $(shell cat fixes.yml | grep -c "Error") -gt 0 ] && exit 1

replacements.xml: $(ALL_SOURCES)
	clang-format -output-replacements-xml $(ALL_SOURCES) > replacements.xml

fixes.yml: $(ALL_SOURCES)
	clang-tidy --checks='*' -header-filter=.* --export-fixes=fixes.yml $(ALL_SOURCES)
