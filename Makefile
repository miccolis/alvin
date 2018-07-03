.PHONY: verify clean vendor
verify:
	/Applications/Arduino.app/Contents/MacOS/Arduino --pref build.path=./build --verify --preserve-temp-files alvin.ino

upload:
	/Applications/Arduino.app/Contents/MacOS/Arduino --pref build.path=./build --upload --preserve-temp-files alvin.ino

clean:
	rm -rf ./build/*

vendor/rfid:
	curl -L -o ./vendor/rfid.zip https://github.com/miguelbalboa/rfid/archive/master.zip 
	unzip -d ./vendor ./vendor/rfid
	mv ./vendor/rfid-master ./vendor/rfid
	rm ./vendor/rfid.zip

vendor/Adafruit-GFX-Library:
	curl -L -o ./vendor/Adafruit-GFX-Library.tar.gz https://github.com/adafruit/Adafruit-GFX-Library/archive/v1.2.3.tar.gz
	cd vendor && tar xzf Adafruit-GFX-Library.tar.gz
	cd vendor && rm Adafruit-GFX-Library.tar.gz

vendor: vendor/Adafruit-GFX-Library
