import os
import tensorflow as tf
import numpy as np
from tensorflow.keras.preprocessing import image
from tensorflow.keras.applications.inception_v3 import InceptionV3, preprocess_input, decode_predictions

def isViableModel(str_path_model:str) -> bool:
    list_ext = [".h5",".pb"]
    return isViable(str_path_model,list_ext)

def isViableImage(str_path_image:str) ->bool:
     list_ext = [".jpg",".jpeg",".png"]
     return isViable(str_path_image,list_ext)

def isViable(str_path:str,list_extensions:list) ->bool:
     result = False
     for i in range(len(list_extensions)):
          result = result or str_path.endswith(str(list_extensions[i]))
     return result and os.path.exists(str_path)


def preprocess_image(image_path, target_size):
    img = image.load_img(image_path, target_size=target_size)
    img_array = image.img_to_array(img)
    img_array = np.expand_dims(img_array, axis=0)
    img_array = img_array / 255.0  # Normalizacja
    return img_array

def getResult(str_path_image, str_path_model) -> list:
    if isViableImage(str_path_image) and isViableModel(str_path_model):
        try:
            """
            # Ładowanie modelu
            model = tf.keras.models.load_model(str_path_model)
            
            # Ustalanie rozmiaru wejściowego modelu
            input_shape = model.input_shape[1:3]  # (wysokość, szerokość)

            # Przetwarzanie obrazu
            img_array = preprocess_image(str_path_image, target_size=input_shape)

            # Predykcja
            predictions = model.predict(img_array)

            # Zakładam, że model ma warstwę wyjściową z prawdopodobieństwami
            # i etykiety są pozycjonowane w kolejności indeksów (np. `0` = 'cat', `1` = 'dog').
            labels = range(len(predictions[0]))  # Generowanie domyślnych etykiet, jeśli brak metadanych

            # Tworzenie listy wyników
            result = []
            for label, prob in zip(labels, predictions[0]):
                result.append(f"label{label}")
                result.append(float(prob))
                """
            # Ładowanie modelu InceptionV3 (pretrenowanego na ImageNet)
            model = InceptionV3(weights='imagenet')

    # Załadowanie obrazu do klasyfikacji
            img = image.load_img(str_path_image, target_size=(299, 299))

    # Konwertowanie obrazu na tablicę numpy
            img_array = image.img_to_array(img)

    # Zwiększanie wymiarów obrazu (dodanie 'batch' - rozmiaru wsadu)
            img_array = np.expand_dims(img_array, axis=0)

    # Przetwarzanie obrazu do odpowiedniego formatu (normalizacja)
            img_array = preprocess_input(img_array)

    # Przewidywanie klasy
            predictions = model.predict(img_array)

    # Dekodowanie wyników predykcji
            decoded_predictions = decode_predictions(predictions, top=3)[0]

    # Wyświetlenie wyników
            result = []
            for i, (imagenet_id, label, score) in enumerate(decoded_predictions):
                 result.append(label)
                 result.append(float(np.float32(score)))
            return result
        except Exception as e:
            print(f"Error while processing: {e}")
            return [-1]
    else:
        return [-1]



def cli():
     exit = "exit"
     while True:
          lineImage = input("wpisz path image:")
          lineModel = input("wpisz path Model:")

          if(lineImage == exit or lineModel == exit):break
          else:
               b1 = isViableImage(lineImage)
               b2 = isViableModel(lineModel)
               print("result image: "+str(b1)+"\n")
               print("result model: "+str(b2)+"\n")
               if(b1 and b2):
                   print(getResult(lineImage, lineModel))

cli()




          
     