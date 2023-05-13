// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <cstdint>
#include <algorithm>

namespace Detail
{
	/**
	 * @brief Neuron count structure.
	 * This structure contains information regarding the neuron count using layers as template arguments.
	 *
	 * @tparam Total The total number of neurons up until this point.
	 * @tparam Layer The current layer's neuron count.
	 * @tparam Rest The rest of the neuron counts.
	 */
	template <uint32_t Total, uint8_t Layer, uint8_t... Rest>
	struct NeuronCount : public NeuronCount<Total + Layer, Rest...>
	{
	};

	/**
	 * @brief Neuron count structure specialization.
	 *
	 * @tparam Total The total number of layers up until this point.
	 * @tparam Layer The current layer's neuron count.
	 */
	template <uint32_t Total, uint8_t Layer>
	struct NeuronCount<Total, Layer>
	{
		// The total neuron count.
		static constexpr uint32_t Count = Total + Layer;
	};

	/**
	 * @brief Bias count structure.
	 * This contains information about the total number of biases in the neural network.
	 *
	 * @tparam Total The bias count till this point.
	 * @tparam Layer The current layer's neuron count. This is neglected as the first is the input layer.
	 * @tparam Rest The rest of the neuron counts.
	 */
	template <uint32_t Total, uint8_t Layer, uint8_t... Rest>
	struct BiasCount final : public NeuronCount<Total, Rest...>
	{
	};

	/**
	 * @brief Connection count structure.
	 * This contains information regarding the total connection count of the network.
	 *
	 * @tparam Total The number of connections till this point.
	 * @tparam CurrentLayer The current layer's neuron count.
	 * @tparam NextLayer The next layer's neuron count.
	 * @tparam Rest The rest of the neuron counts.
	 */
	template <uint32_t Total, uint8_t CurrentLayer, uint8_t NextLayer, uint8_t... Rest>
	struct ConnectionCount : public ConnectionCount<Total + (CurrentLayer * NextLayer), NextLayer, Rest...>
	{
	};

	/**
	 * @brief Connection count structure specialization.
	 *
	 * @tparam Total The number of connections till this point.
	 * @tparam CurrentLayer The current layer's neuron count.
	 * @tparam NextLayer The next layer's neuron count.
	 */
	template <uint32_t Total, uint8_t CurrentLayer, uint8_t NextLayer>
	struct ConnectionCount<Total, CurrentLayer, NextLayer>
	{
		// The total connection count.
		static constexpr uint32_t Count = Total + (CurrentLayer * NextLayer);
	};

	/**
	 * @brief Output layer index structure.
	 * This structure contains the output layer's index.
	 *
	 * @tparam Offset The offset till this point.
	 * @tparam Layer The current layer's neuron count.
	 * @tparam Rest The rest of the neuron counts.
	 */
	template <uint32_t Offset, uint8_t Layer, uint8_t... Rest>
	struct OutputLayerIndex : public OutputLayerIndex<Offset + Layer, Rest...>
	{
	};

	/**
	 * @brief Output layer index structure specialization.
	 *
	 * @tparam Offset The offset till this point.
	 * @tparam Layer The current layer's neuron count.
	 */
	template <uint32_t Offset, uint8_t Layer>
	struct OutputLayerIndex<Offset, Layer>
	{
		static constexpr uint32_t Index = Offset;
		static constexpr uint32_t Size = Layer;
	};
} // namespace Detail

/**
 * @brief Model structure.
 * This contains the required values to initialize the neural network with.
 *
 * @tparam Weights The number of weights stored.
 * @tparam Biases The number of biases stored.
 */
template <uint32_t Weights, uint32_t Biases>
struct Model final
{
	float m_Weights[Weights] = {1.0f};
	float m_Biases[Biases] = {0.0f};
};

/**
 * @brief Neural network class.
 *
 * @tparam InputLayer The input layer size.
 * @tparam Layers The input, hidden and output layers' neuron counts.
 */
template <uint8_t InputLayer, uint8_t... Layers>
class NeuralNetwork final
{
public:
	static constexpr uint32_t g_LayerCount = 1 + sizeof...(Layers);

	static constexpr uint32_t g_NeuronCount = Detail::NeuronCount<0, InputLayer, Layers...>::Count;
	static constexpr uint32_t g_ConnectionCount = Detail::ConnectionCount<0, InputLayer, Layers...>::Count;
	static constexpr uint32_t g_BiasCount = Detail::BiasCount<0, InputLayer, Layers...>::Count;

	static constexpr uint32_t g_InputLayerSize = InputLayer;

	static constexpr uint32_t g_OutputLayerIndex = Detail::OutputLayerIndex<0, InputLayer, Layers...>::Index;
	static constexpr uint32_t g_OutputLayerSize = Detail::OutputLayerIndex<0, InputLayer, Layers...>::Size;

	using ModelType = Model<g_ConnectionCount, g_BiasCount>;

public:
	/**
	 * @brief Construct a new Neural Network object.
	 */
	NeuralNetwork() = default;

	/**
	 * @brief Construct a new Neural Network object.
	 *
	 * @param model The model to initialize the network with.
	 */
	explicit NeuralNetwork(const ModelType &model)
	{
		std::copy_n(model.m_Weights, g_ConnectionCount, m_Weights);
		std::copy_n(model.m_Biases, g_BiasCount, m_Biases);
	}

	/**
	 * @brief Load the model to the neural network.
	 *
	 * @param model The model to load and initialize the parameters with.
	 */
	void load(const ModelType &model)
	{
		std::copy_n(model.m_Weights, g_ConnectionCount, m_Weights);
		std::copy_n(model.m_Biases, g_BiasCount, m_Biases);
	}

	/**
	 * @brief Unload the internal data to a model.
	 *
	 * @return ModelType The unloaded model.
	 */
	[[nodiscard]] ModelType unload() const
	{
		ModelType model;
		std::copy_n(m_Weights, g_ConnectionCount, model.m_Weights);
		std::copy_n(m_Biases, g_BiasCount, model.m_Biases);

		return model;
	}

	/**
	 * @brief Run the neural network.
	 *
	 * @param inputs The inputs to provide the neural network with. Make sure the input count matches the input layer's neuron count.
	 */
	void run(const std::array<float, g_InputLayerSize> &inputs)
	{
		std::copy_n(inputs.data(), g_InputLayerSize, m_Activations);
		propagateForward();
	}

	/**
	 * @brief Get the output of a given neuron using it's index.
	 *
	 * @param index The index of the output neuron.
	 * @return The activation value.
	 */
	float getOutput(uint8_t index) const
	{
		return m_Activations[g_OutputLayerIndex + index];
	}

	/**
	 * @brief Train the neural network using the target values.
	 *
	 * @param expected The expected output values. Make sure the output count matches the output layer's neuron count.
	 */
	void train(const std::array<float, g_OutputLayerSize> &expected)
	{
		for (uint32_t i = 0; i < g_OutputLayerSize; i++)
			m_ErrorMatrix[i] = std::pow(expected[i] - getOutput(i + g_OutputLayerIndex), 2);

		propagateBackward();
	}

private:
	/**
	 * @brief Perform forward propagation on the neural network.
	 */
	void propagateForward()
	{
		static constexpr uint8_t layerSizes[] = {Layers...};

		uint32_t biasIndex = 0;
		uint32_t activationIndex = 0;
		uint32_t weightFactor = g_InputLayerSize;
		uint32_t previousLayerSize = g_InputLayerSize;

		for (uint8_t layer = 0; layer < g_LayerCount - 1; layer++)
		{
			const auto currentLayerSize = layerSizes[layer];
			const auto activationEnd = previousLayerSize + currentLayerSize;

			for (uint32_t i = previousLayerSize; i < activationEnd; i++)
			{
				float activation = m_Biases[biasIndex + i];

				for (uint32_t j = activationIndex; j < currentLayerSize; j++)
					activation += m_Activations[j] * m_Weights[(i * weightFactor) + j];

				m_Activations[i] = activation;
			}

			weightFactor = currentLayerSize;
			biasIndex += currentLayerSize;
			previousLayerSize += currentLayerSize;
		}
	}

	/**
	 * @brief Perform back propagation on the neural network.
	 */
	void propagateBackward()
	{
		m_MSE = 0.0f;
		for (const auto error : m_ErrorMatrix)
			m_MSE += error;

		m_MSE /= g_NeuronCount;
	}

private:
	float m_Weights[g_ConnectionCount] = {1.0f};
	float m_Activations[g_NeuronCount] = {0.0f};
	float m_Biases[g_BiasCount] = {0.0f};
	float m_ErrorMatrix[g_OutputLayerSize] = {0.0f};

	float m_MSE = 0.0f;
};
