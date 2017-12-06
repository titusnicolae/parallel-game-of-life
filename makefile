all:
	g++ -o game game.cpp -O3 -fopenmp && time ./game
	time ./gif.py
	time ffmpeg -f image2 -i output/out%03d.png -vcodec mpeg4 -b 18000k video.avi -y -loglevel panic
	xdg-open video.avi
	rm output/out*.png
