from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing import image
import numpy as np
import os



# Lista folderów z klasami na stałe
folder_names = ["Apple 6",
                "Apple Braeburn 1",
                "Apple Crimson Snow 1",
                "Apple Golden 1",
                "Apple Golden 2",
                "Apple Golden 3",
                "Apple Granny Smith 1",
                "Apple hit 1",
                "Apple Pink Lady 1",
                "Apple Red 1",
                "Apple Red 2",
                "Apple Red 3",
                "Apple Red Delicious 1",
                "Apple Red Yellow 1",
                "Apple Red Yellow 2",
                "Apricot 1",
                "Avocado 1",
                "Avocado ripe 1",
                "Banana 1",
                "Banana Lady Finger 1",
                "Banana Red 1",
                "Beetroot 1",
                "Blueberry 1",
                "Cabbage white 1",
                "Cactus fruit 1",
                "Cantaloupe 1",
                "Cantaloupe 2",
                "Carambula 1",
                "Carrot 1",
                "Cauliflower 1",
                "Cherry 1",
                "Cherry 2",
                "Cherry Rainier 1",
                "Cherry Wax Black 1",
                "Cherry Wax Red 1",
                "Cherry Wax Yellow 1",
                "Chestnut 1",
                "Clementine 1",
                "Cocos 1",
                "Corn 1",
                "Corn Husk 1",
                "Cucumber 1",
                "Cucumber 3",
                "Cucumber Ripe 1",
                "Cucumber Ripe 2",
                "Dates 1",
                "Eggplant 1",
                "Eggplant long 1",
                "Fig 1",
                "Ginger Root 1",
                "Granadilla 1",
                "Grape Blue 1",
                "Grape Pink 1",
                "Grape White 1",
                "Grape White 2",
                "Grape White 3",
                "Grape White 4",
                "Grapefruit Pink 1",
                "Grapefruit White 1",
                "Guava 1",
                "Hazelnut 1",
                "Huckleberry 1",
                "Kaki 1",
                "Kiwi 1",
                "Kohlrabi 1",
                "Kumquats 1",
                "Lemon 1",
                "Lemon Meyer 1",
                "Limes 1",
                "Lychee 1",
                "Mandarine 1",
                "Mango 1",
                "Mango Red 1",
                "Mangostan 1",
                "Maracuja 1",
                "Melon Piel de Sapo 1",
                "Mulberry 1",
                "Nectarine 1",
                "Nectarine Flat 1",
                "Nut Forest 1",
                "Nut Pecan 1",
                "Onion Red 1",
                "Onion Red Peeled 1",
                "Onion White 1",
                "Orange 1",
                "Papaya 1",
                "Passion Fruit 1",
                "Peach 1",
                "Peach 2",
                "Peach Flat 1",
                "Pear 1",
                "Pear 2",
                "Pear 3",
                "Pear Abate 1",
                "Pear Forelle 1",
                "Pear Kaiser 1",
                "Pear Monster 1",
                "Pear Red 1",
                "Pear Stone 1",
                "Pear Williams 1",
                "Pepino 1",
                "Pepper Green 1",
                "Pepper Orange 1",
                "Pepper Red 1",
                "Pepper Yellow 1",
                "Physalis 1",
                "Physalis with Husk 1",
                "Pineapple 1",
                "Pineapple Mini 1",
                "Pitahaya Red 1",
                "Plum 1",
                "Plum 2",
                "Plum 3",
                "Pomegranate 1",
                "Pomelo Sweetie 1",
                "Potato Red 1",
                "Potato Red Washed 1",
                "Potato Sweet 1",
                "Potato White 1",
                "Quince 1",
                "Rambutan 1",
                "Raspberry 1",
                "Redcurrant 1",
                "Salak 1",
                "Strawberry 1",
                "Strawberry Wedge 1",
                "Tamarillo 1",
                "Tangelo 1",
                "Tomato 1",
                "Tomato 2",
                "Tomato 3",
                "Tomato 4",
                "Tomato Cherry Red 1",
                "Tomato Heart 1",
                "Tomato Maroon 1",
                "Tomato not Ripened 1",
                "Tomato Yellow 1",
                "Walnut 1",
                "Watermelon 1",
                "Zucchini 1",
                "Zucchini dark 1"]  # Zastąp to rzeczywistymi nazwami folderów

def isPathModelCorrect(path):
    # Sprawdź, czy plik modelu istnieje i ma odpowiedni format
    return os.path.exists(path) and path.endswith(".h5")

def isPathImageCorrect(path):
    # Sprawdź, czy plik obrazu istnieje i ma odpowiedni format
    return os.path.exists(path) and (path.endswith(".jpg") or path.endswith(".png"))

def getResult(img_path, model_path):
    # Sprawdź, czy ścieżka do modelu jest poprawna
    if not isPathModelCorrect(model_path):
        print(f"Model nie istnieje lub ma niepoprawny format: {model_path}")
        return []

    # Załaduj model
    model = load_model(model_path)
    print(f"Model {model_path} załadowany pomyślnie!")

    # Parametry obrazu (muszą być zgodne z treningiem modelu)
    img_height = 150
    img_width = 150

    # Sprawdź, czy ścieżka do obrazu jest poprawna
    if not isPathImageCorrect(img_path):
        print(f"Obraz nie istnieje lub ma niepoprawny format: {img_path}")
        return []

    # Załaduj obraz, zmień rozmiar i przekształć na tablicę NumPy
    img = image.load_img(img_path, target_size=(img_height, img_width))
    img_array = image.img_to_array(img)  # Zamiana na tablicę NumPy
    img_array = np.expand_dims(img_array, axis=0)  # Dodaj wymiar batcha
    img_array = img_array / 255.0  # Normalizacja (jeśli była stosowana podczas treningu)

    # Wykonaj predykcję
    predictions = model.predict(img_array)

    # Przekształć wynik na listę etykiet i prawdopodobieństw
    result = []
    for i, pred in enumerate(predictions[0]):
        result.append((folder_names[i], pred*100))

    return result

def cli():
    print(getResult(input('wpisz image:'),input('wpisz model:')))
