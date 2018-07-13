.PHONY: verify upload clean 
verify:
	/Applications/Arduino.app/Contents/MacOS/Arduino --pref build.path=./build/ --verify --preserve-temp-files alvin.ino

upload:
	/Applications/Arduino.app/Contents/MacOS/Arduino --pref build.path=./build/ --upload --preserve-temp-files alvin.ino

clean:
	rm -rf ./build/*
