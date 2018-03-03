mkdir build
cd build

cmake ..
make

cd src

zip framebot-bin.zip libframebot.a libframebot_.so

cd ../../
ls -LR