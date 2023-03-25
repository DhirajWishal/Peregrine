// Copyright 2023 Dhiraj Wishal
// SPDX-License-Identifier: Apache-2.0

#pragma once

/**
 * @brief Data link interface class.
 * All data links are required to be derived from this class and attached to the input system when initialized.
 */
class IDataLink
{
public:
	/**
	 * @brief Construct a new IInputController object.
	 */
	IDataLink() = default;

	/**
	 * @brief On initialize pure virtual method.
	 * This metod is intended to be used to initialize the data link.
	 * This method gets called once the data link is attached to the input system.
	 */
	virtual void onInitialize() = 0;

	/**
	 * @brief On update pure virtual method.
	 * This method is intended to be used to update the data link and to poll the latest information.
	 */
	virtual void onUpdate() = 0;
};