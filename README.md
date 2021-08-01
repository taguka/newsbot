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
[VectorsRu.ipynb](https://github.com/taguka/newsbot/blob/main/scripts/VectorsRu.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1KbD7gKNCMhkoOA7_vVf32XrfaaBNhRlV)
* Russian fasttext category classifier training:
[CatTrainRu.ipynb](https://github.com/taguka/newsbot/blob/main//scripts/CatTrainRu.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1IwkAy4W1Rg36ZMVbhOWCUhfGyBp_AFpe)
* Russian text embedder with **triplet loss** training (v1):
[SimilarityRuTorchTripletLoss.ipynb](https://github.com/taguka/newsbot/blob/main/scripts/SimilarityRuTorchTripletLoss.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1umK5TbUR3YBy3rKFcxjgLNbUXt0SsZan)
* PageRank rating calculation:
[PageRankRating.ipynb](https://github.com/taguka/newsbot/blob/main/scripts/PageRankRating.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1fD3A5XkCXMNve51vWDQIIdLkPLdYebPX)
* Russian **ELMo-based** sentence embedder training (not used):
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1Q0S5OvramxxqQZnaSIH8xWfmOsWeKhIz)

* English FastText vectors training:
[VectorsEn.ipynb](https://github.com/taguka/newsbot/blob/main/scripts/VectorsEn.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1eXIGaw9n7PSgUD_QBucmgEjgjIOotdqg)
* English fasttext category classifier training:
[CatTrainEn.ipynb](https://github.com/taguka/newsbot/blob/main//scripts/CatTrainEn.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/1UOWpkq84AHnz9fWxtu-_XAr48-FOQ24g)
* English text embedder with **triplet loss** training (v1):
[SimilarityEnTorchTripletLoss.ipynb](https://github.com/taguka/newsbot/blob/main/scripts/SimilarityEnTorchTripletLoss.ipynb)
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/drive/14pTBKd4inJ97WawVGY7bVTgGmyklBM-W)




