## Install
Prerequisites: CMake, Boost
```
$ sudo apt-get install cmake libboost-all-dev build-essential libjsoncpp-dev uuid-dev protobuf-compiler libprotobuf-dev
```

For MacOS
```
$ brew install boost jsoncpp ossp-uuid protobuf
```


If you got zip archive, just go to building binary

To download code and models:
```
$ git clone https://github.com/taguka/newsbot
$ cd newsbot
$ git submodule update --init --recursive
$ bash download_models.sh
$ wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.5.0%2Bcpu.zip
$ unzip libtorch-cxx11-abi-shared-with-deps-1.5.0+cpu.zip
```

For MacOS use https://download.pytorch.org/libtorch/cpu/libtorch-macos-1.5.0.zip

To build binary (in "newsbot" dir):
```
$ mkdir build && cd build && Torch_DIR="../libtorch" cmake -DCMAKE_BUILD_TYPE=Release .. && make -j4
```

To download datasets:
```
$ bash download_data.sh
```

Run on sample:
```
./build/newsbot top data --ndocs 10000

```

Newsviewer: 

```
bash build_viewer.sh viewer/templates input_file.json output_folder
```


## Training

* Russian FastText vectors training:
[VectorsRu.ipynb](https://github.com/IlyaGusev/tgcontest/blob/master/scripts/VectorsRu.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1QeyhqsHy5MO3yzvsn446LsqK_PqOjIVb)
* Russian fasttext category classifier training:
[CatTrainRu.ipynb](https://github.com/IlyaGusev/tgcontest/blob/master/scripts/CatTrainRu.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1U7Wxm5eDnrBRWE_logCSJIq6DzTFV0Zo)
* Russian text embedder with **triplet loss** training (v3):
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1vp_qbWKtqtqgNLW5Upp4Gh2UL36zdTvT)
* English FastText vectors training:
[VectorsEn.ipynb](https://github.com/IlyaGusev/tgcontest/blob/master/scripts/VectorsEn.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1lbmgJ_iGBdwKdkU_1l1-WZuO7XbYZlWQ)
* English fasttext category classifier training:
[CatTrainEn.ipynb](https://github.com/IlyaGusev/tgcontest/blob/master/scripts/CatTrainEn.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1ayg5dtA_KdhzVehN4-_EiyIcwRhBVSob)
* English text embedder with **triplet loss** training (v3):
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1o1B50aktpHJmEzHCQ8lPV3yZOtKSTXa3)
* PageRank rating calculation:
[PageRankRating.ipynb](https://github.com/IlyaGusev/tgcontest/blob/master/scripts/PageRankRating.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1bd35S0rl_Uysiuz_7fmkYRArzNcP-wZB)
* Russian **ELMo-based** sentence embedder training (not used):
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1Q0S5OvramxxqQZnaSIH8xWfmOsWeKhIz)
* XLM-RoBERTa pseudo-labeling for categorization: [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1fEmNPi41mnxLrc4hqamqi72xDCCH0Ima)





