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
	 * @tparam Total THe number of connections till this point.
	 * @tparam CurrentLayer The current layer's neuron count.
	 * @tparam NextLayer The next layer's neuron count.
	 */
	template <uint32_t Total, uint8_t CurrentLayer, uint8_t NextLayer>
	struct ConnectionCount<Total, CurrentLayer, NextLayer>
	{
		// The total connection count.
		static constexpr uint32_t Count = Total + (CurrentLayer * NextLayer);
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
 * @tparam Layers The input, hidden and output layers' neuron counts.
 */
template <uint8_t... Layers>
class NeuralNetwork final
{
public:
	static constexpr uint32_t g_LayerCount = sizeof...(Layers);
	static constexpr uint8_t g_LayerSizes[] = {Layers...};

	static constexpr uint32_t g_NeuronCount = Detail::NeuronCount<0, Layers...>::Count;
	static constexpr uint32_t g_ConnectionCount = Detail::ConnectionCount<0, Layers...>::Count;
	static constexpr uint32_t g_BiasCount = Detail::BiasCount<0, Layers...>::Count;

	static constexpr uint32_t g_OutputLayerIndex = g_LayerCount - 1;
	static constexpr uint32_t g_OutputLayerSize = g_LayerSizes[g_OutputLayerIndex];

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
	 * @tparam Inputs The input types.
	 * @param inputs The inputs to provide the neural network with. Make sure the input count matches the input layer's neuron count.
	 */
	template <class... Inputs>
	void run(Inputs &&...inputs)
	{
		static_assert(sizeof...(inputs) == g_LayerSizes[0], "Invalid input argument count! Make sure it equals to "
															"the input layer size.");

		setInputs(0, std::forward<Inputs>(inputs)...);
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
	 * @tparam Outputs The expected output value types.
	 * @param expected The expected output values. Make sure the output count matches the output layer's neuron count.
	 */
	template <class... Outputs>
	void train(Outputs &&...expected)
	{
		static_assert(sizeof...(expected) == g_LayerSizes[g_LayerCount - 1],
					  "Invalid output argument count! Make sure it equals to "
					  "the output layer size.");

		calculateCost(0, std::forward<Outputs>(expected)...);
		propagateBackward();
	}

private:
	/**
	 * @brief Set the values to the input neurons.
	 *
	 * @tparam Input The input neuron type.
	 * @tparam Inputs The input neuron types (the rest).
	 * @param index The index of the neuron to set.
	 * @param input The input value to set to the current neuron.
	 * @param inputs The rest of the neurons.
	 */
	template <class Input, class... Inputs>
	void setInputs(uint32_t index, Input &&input, Inputs &&...inputs)
	{
		m_Activations[index] = std::move(input);

		if constexpr (sizeof...(inputs) > 0)
			setInputs(index + 1, std::forward<Inputs>(inputs)...);
	}

	/**
	 * @brief Perform forward propagation on the neural network.
	 */
	void propagateForward()
	{
		uint32_t biasIndex = 0;
		uint32_t activationIndex = 0;
		uint32_t weightFactor = g_LayerSizes[0];
		uint32_t previousLayerSize = g_LayerSizes[0];

		for (uint8_t layer = 1; layer < g_LayerCount; layer++)
		{
			const auto currentLayerSize = g_LayerSizes[layer];
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

	/**
	 * @brief Calculate the cost of the output using it's expected values.
	 *
	 * @tparam Output The output type.
	 * @tparam Outputs The output types.
	 * @param index The index of the current output neuron.
	 * @param output The expected output of the current neuron.
	 * @param outputs The rest of the expected values.
	 */
	template <class Output, class... Outputs>
	void calculateCost(uint32_t index, Output &&output, Outputs &&...outputs)
	{
		m_ErrorMatrix[index] = std::pow(output - getOutput(index), 2);

		if constexpr (sizeof...(outputs) > 0)
			calculateCost(index + 1, std::forward<Outputs>(outputs)...);
	}

private:
	float m_Weights[g_ConnectionCount] = {1.0f};
	float m_Activations[g_NeuronCount] = {0.0f};
	float m_Biases[g_BiasCount] = {0.0f};
	float m_ErrorMatrix[g_OutputLayerSize] = {0.0f};

	float m_MSE = 0.0f;
};