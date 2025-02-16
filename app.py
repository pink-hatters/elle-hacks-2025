from flask import Flask, render_template, jsonify, request
from google import genai

# Initialize the Flask app
app = Flask(__name__)

# Initialize the GenAI client
client = genai.Client(api_key="YOUR_API_KEY")

@app.route('/')
def home():
    # You can render the HTML template (index.html) with any necessary data
    return render_template('index.html')

@app.route('/generate-content', methods=['POST'])
def generate_content():
    # Extract the values from the progress bars (sent from the frontend)
    affection = request.json.get('affection', 0)
    rest = request.json.get('rest', 0)
    food = request.json.get('food', 0)

    # Use the GenAI API to generate content based on progress values
    response = client.models.generate_content(
        model="gemini-2.0-flash",
        contents=f"Please generate a message based on the following: Affection: {affection}, Rest: {rest}, Food: {food}"
    )
    
    # Send the response back to the frontend
    return jsonify({"message": response.text})

if __name__ == "__main__":
    app.run(debug=True)
