kernel_debug :
	make -C Kernel debug
	make -C Public debug
	g++ -g -pg ./Debug/*.o -ldl -lpthread -o Kernel_D
kernel_release :
	make -C Kernel release
	make -C Public release
	g++ -O3 ./Release/*.o -ldl -lpthread -o Kernel_R
clean:
	find ./ -name "*.o" | xargs rm -f
	rm -f Kernel_D Kernel_R
