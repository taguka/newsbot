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

## Models
* Language detection model (2 round): [lang_detect_v10.ftz](https://www.dropbox.com/s/hoapmnvqlknmu6v/lang_detect_v10.ftz)
* Russian FastText vectors (2 round): [ru_vectors_v3.bin](https://www.dropbox.com/s/vttjivmmxw7leea/ru_vectors_v3.bin)
* Russian categories detection model (2 round): [ru_cat_v5.ftz](https://www.dropbox.com/s/23x35wuet280eh6/ru_cat_v5.ftz)
* English FastText vectors (2 round): [en_vectors_v3.bin](https://www.dropbox.com/s/6aaucelizfx7xl6/en_vectors_v3.bin)
* English categories detection model (2 round): [en_cat_v5.ftz](https://www.dropbox.com/s/luh60dd0uw8p9ar/en_cat_v5.ftz)
* PageRank-based agency rating: [pagerank_rating.txt](https://www.dropbox.com/s/0o9xr2pwuqeh17k/pagerank_rating.txt)
* Alexa agency rating: [alexa_rating_4_fixed.txt](https://www.dropbox.com/s/fry1gsd1mans9jm/alexa_rating_4_fixed.txt)
* XLM-RoBERTa for categorization (pytorch-lightning checkpoint): [xlmr_en_ru_cat_v1.tar.gz](https://www.dropbox.com/s/y6leppzf2l43eqo/xlmr_en_ru_cat_v1.tar.gz)




