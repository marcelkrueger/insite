# coding: utf-8

from __future__ import absolute_import
from datetime import date, datetime  # noqa: F401

from typing import List, Dict  # noqa: F401

from access_node.models.base_model_ import Model
from access_node import util


class NestNodeModel(Model):
    """NOTE: This class is auto generated by OpenAPI Generator (https://openapi-generator.tech).

    Do not edit the class manually.
    """

    def __init__(self, name=None, parameters=None):  # noqa: E501
        """NestNodeModel - a model defined in OpenAPI

        :param name: The name of this NestNodeModel.  # noqa: E501
        :type name: str
        :param parameters: The parameters of this NestNodeModel.  # noqa: E501
        :type parameters: object
        """
        self.openapi_types = {
            'name': str,
            'parameters': object
        }

        self.attribute_map = {
            'name': 'name',
            'parameters': 'parameters'
        }

        self._name = name
        self._parameters = parameters

    @classmethod
    def from_dict(cls, dikt) -> 'NestNodeModel':
        """Returns the dict as a model

        :param dikt: A dict.
        :type: dict
        :return: The NestNodeModel of this NestNodeModel.  # noqa: E501
        :rtype: NestNodeModel
        """
        return util.deserialize_model(dikt, cls)

    @property
    def name(self):
        """Gets the name of this NestNodeModel.


        :return: The name of this NestNodeModel.
        :rtype: str
        """
        return self._name

    @name.setter
    def name(self, name):
        """Sets the name of this NestNodeModel.


        :param name: The name of this NestNodeModel.
        :type name: str
        """

        self._name = name

    @property
    def parameters(self):
        """Gets the parameters of this NestNodeModel.


        :return: The parameters of this NestNodeModel.
        :rtype: object
        """
        return self._parameters

    @parameters.setter
    def parameters(self, parameters):
        """Sets the parameters of this NestNodeModel.


        :param parameters: The parameters of this NestNodeModel.
        :type parameters: object
        """

        self._parameters = parameters
