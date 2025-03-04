"cpp": "cd $dir 
&& g++ $fileName  -Wall -Wextra 
-fsanitize=undefined -DLOCAL -D_GLIBCXX_DEBUG 
-std=c++17 -g -O2 -o $fileNameWithoutExt 
&& $dir/$fileNameWithoutExt",